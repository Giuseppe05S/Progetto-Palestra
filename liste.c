//file liste.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "corso.h"

struct c_list {
    struct node *first;
    int size;
};
struct node{
    Corso c;
    struct node *next;
};
//Prototipi dichiarati in quanto chiamati
//prima di essere implementati
static struct node* insertNode(struct node* l, int pos, Corso val);
static struct node* removeNode(struct node* l, int pos);
/*
•  Funzione: newList
•  -----------------------------------
•  Crea una nuova lista vuota e restituisce la lista creata.
*
•  Parametri:
*   Nessuno.
*
•  Pre-condizione:
*   Nessuna.
*
•  Post-condizione:
*   Viene creata una nuova lista vuota con first = NULL e size = 0.
*   Restituisce il puntatore alla lista creata o NULL se l'allocazione fallisce.
*
•  Come funziona:
•  - Alloca memoria per la struttura c_list.
•  - Inizializza first a NULL e size a 0.
•  - Restituisce il puntatore alla lista creata.
*/
list newList(void){
    struct c_list *l;
    l = malloc(sizeof(struct c_list));
    if (l != NULL){
        l->first = NULL;
        l->size = 0;
    }
    return l;
}
/*
•  Funzione: isEmpty
•  -----------------------------------
•  Verifica se una lista è vuota.
*
•  Parametri:
*   l: lista da verificare.
*
•  Pre-condizione:
*   Nessuna (gestisce anche liste NULL).
*
•  Post-condizione:
*   Restituisce 1 se la lista è vuota o NULL, 0 altrimenti.
*
•  Come funziona:
•  - Controlla se l è NULL o se l->first è NULL.
•  - Restituisce 1 in caso affermativo, 0 altrimenti.
*/
int isEmpty(list l){
  if (l == NULL||l->first == NULL){
	  return 1;
	}
  return 0;
}
/*
•  Funzione: insertList
•  -----------------------------------
•  Inserisce un corso in una posizione specifica della lista.
*
•  Parametri:
*   l: lista in cui inserire.
*   pos: posizione di inserimento (0 = inizio).
*   val: corso da inserire.
*
•  Pre-condizione:
*   l deve essere una lista valida (non NULL).
*   pos deve essere >= 0 e <= dimensione lista.
*
•  Post-condizione:
*   Il corso viene inserito nella posizione specificata.
*   La dimensione della lista viene incrementata di 1.
*   Restituisce 1 se successo, 0 se errore.
*
•  Come funziona:
•  - Chiama insertNode per inserire il nuovo nodo.
•  - Aggiorna il puntatore first se necessario.
•  - Incrementa la dimensione della lista.
•  - Restituisce il risultato dell'operazione.
*/
int insertList(list l, int pos, Corso val){
    struct node* tmp = insertNode(l->first, pos, val); // Chiama insertNode per inserire un nuovo nodo nella lista
    if(tmp == NULL)
      return 0; // Se insertNode restituisce NULL, l'inserimento è fallito (es. errore di allocazione memoria), restituisce 0
    l->first = tmp; // Aggiorna il puntatore al primo nodo della lista con il possibile nuovo primo nodo (se inserito in testa)
    l->size++; // Incrementa la dimensione della lista di uno

    return 1; // Restituisce 1 per indicare che l'inserimento è avvenuto con successo
}
/*
•  Funzione: insertNode (static)
•  -----------------------------------
•  Funzione ausiliaria per inserire un nodo nella lista concatenata.
*
•  Parametri:
*   l: primo nodo della lista.
*   pos: posizione di inserimento.
*   val: valore da inserire.
*
•  Pre-condizione:
*   pos deve essere valida rispetto alla lunghezza della lista.
*
•  Post-condizione:
*   Viene creato e inserito un nuovo nodo nella posizione specificata.
*   Restituisce il nuovo primo nodo della lista o NULL se errore.
*
•  Come funziona:
•  - Alloca memoria per il nuovo nodo.
•  - Se pos = 0, inserisce in testa alla lista.
•  - Altrimenti scorre fino alla posizione desiderata.
•  - Collega il nuovo nodo nella catena.
•  - Restituisce il puntatore al primo nodo.
*/
static struct node* insertNode(struct node* l, int pos, Corso val){
    struct node *new, *prec = l; // 'new' è il nuovo nodo da inserire, 'prec' è il puntatore al nodo precedente nella lista
    int i = 0;

    new = malloc(sizeof(struct node)); // Alloca memoria per il nuovo nodo
    if (!new)
      return NULL; // Se l'allocazione fallisce, restituisce NULL

    new->c = val; // Imposta il valore del nuovo nodo

    if (pos == 0){ // Se l'inserimento deve avvenire in testa alla lista
        new->next = l; // Il nuovo nodo punta al primo nodo attuale della lista
        return new; // Restituisce il nuovo nodo, che è ora la testa della lista
    }

    // Scorre la lista fino alla posizione desiderata o fino alla fine della lista
    while (i < pos - 1 && prec != NULL) {
        prec = prec->next; // Sposta il puntatore al nodo successivo
        i++; // Incrementa il contatore
    }

    if (prec == NULL){ // Se prec è NULL, la lista è più corta della posizione desiderata
        free(new); // Libera la memoria allocata per il nuovo nodo
        return NULL; // Restituisce NULL per indicare l'impossibilità di inserire il nodo
    }

    // Inserisce il nuovo nodo nella lista
    new->next = prec->next; // Il nuovo nodo punta al nodo successivo di 'prec'
    prec->next = new; // 'prec' ora punta al nuovo nodo

    return l; // Restituisce il puntatore al primo nodo della lista, che non cambia a meno che l'inserimento non sia in testa
}
/*
•  Funzione: removeList
•  -----------------------------------
•  Rimuove un corso da una posizione specifica della lista.
*
•  Parametri:
*   l: lista da cui rimuovere.
*   pos: posizione del corso da rimuovere.
*
•  Pre-condizione:
*   l deve essere una lista valida e non vuota.
*   pos deve essere >= 0 e < dimensione lista.
*
•  Post-condizione:
*   Il corso viene rimosso dalla posizione specificata.
*   La dimensione della lista viene decrementata di 1.
*   Restituisce 1 se successo, 0 se errore.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota.
•  - Chiama removeNode per rimuovere il nodo.
•  - Aggiorna il puntatore first se necessario.
•  - Decrementa la dimensione della lista.
*/
int removeList(list l, int pos){
    if (!l || l->first == NULL || l->size == 0) return 0; // Controlla se la lista è vuota o non inizializzata e restituisce 0 se vero

    l->first = removeNode(l->first, pos); // Chiama la funzione ausiliaria removeNode per rimuovere il nodo e aggiorna il puntatore al primo nodo
    l->size--; // Decrementa la dimensione della lista

    return 1; // Restituisce 1 per indicare che la rimozione è stata completata con successo
}
/*
•  Funzione: removeNode (static)
•  -----------------------------------
•  Funzione ausiliaria per rimuovere un nodo dalla lista concatenata.
*
•  Parametri:
*   l: primo nodo della lista.
*   pos: posizione del nodo da rimuovere.
*
•  Pre-condizione:
*   pos deve essere valida rispetto alla lunghezza della lista.
*
•  Post-condizione:
*   Il nodo viene rimosso e la memoria liberata.
*   Restituisce il nuovo primo nodo della lista.
*
•  Come funziona:
•  - Se pos = 0, rimuove il primo nodo.
•  - Altrimenti scorre fino al nodo precedente a quello da rimuovere.
•  - Scollega il nodo dalla catena e libera la memoria.
•  - Restituisce il puntatore al primo nodo aggiornato.
*/
static struct node* removeNode(struct node* l, int pos){
    struct node* l1; // Puntatore al nodo da eliminare

    if (pos == 0 && l != NULL) { // Se il nodo da eliminare è il primo della lista
        l1 = l; // l1 punta al nodo attuale in testa
        l = l->next; // Sposta la testa della lista al nodo successivo
        free(l1); // Libera la memoria del nodo eliminato
    } else { // Se il nodo da eliminare non è il primo
        int i = 0;
        struct node* prec = l; // prec è usato per tenere traccia del nodo precedente durante lo scorrimento della lista
        while (i < pos - 1 && prec != NULL) { // Scorre la lista fino alla posizione precedente a quella del nodo da eliminare
            prec = prec->next;
            i++;
        }
        // Alla fine del ciclo, se prec non è NULL, allora prec->next è il nodo da eliminare
        if (prec != NULL && prec->next != NULL) { // Controlla se il nodo da eliminare esiste
            l1 = prec->next; // l1 punta al nodo da eliminare
            prec->next = l1->next; // Rimuove il nodo dalla lista collegando il nodo precedente a quello successivo a l1
            free(l1); // Libera la memoria del nodo eliminato
        }
    }
    return l; // Restituisce il puntatore al primo nodo della lista, che potrebbe essere stato aggiornato
}
/*
•  Funzione: reverseList
•  -----------------------------------
•  Crea una nuova lista con i corsi in ordine inverso.
*
•  Parametri:
*   l: lista da invertire.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*
•  Post-condizione:
*   Viene creata una nuova lista con gli elementi in ordine inverso.
*   La lista originale rimane invariata.
*
•  Come funziona:
•  - Crea una nuova lista vuota.
•  - Scorre la lista originale dall'inizio alla fine.
•  - Per ogni corso, lo inserisce in testa alla nuova lista.
•  - Restituisce la nuova lista invertita.
*/
list reverseList(list l){
  list rev=newList();
  Corso temp;
  struct node* curr = l->first;

  while(curr != NULL){
    temp = curr->c;
    if(insertList(rev, 0, temp) == 0){
      printf("Errore nell'inserimento\n");
      exit(1);
    }
    curr = curr->next;
  }
  return rev;
}
/*
•  Funzione: ricercaGenericaLista
•  -----------------------------------
•  Cerca corsi nella lista in base a ID o nome.
*
•  Parametri:
*   l: lista in cui cercare.
*   sel: criterio di ricerca (0=ID, 1=Nome).
*   str: stringa da cercare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   sel deve essere 0 o 1.
*   str deve essere una stringa valida.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente i corsi che corrispondono al criterio.
*   La lista originale rimane invariata.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota.
•  - Crea una nuova lista per i risultati.
•  - Scorre tutta la lista originale.
•  - Per ogni corso, confronta ID o nome con la stringa cercata.
•  - Se corrisponde, inserisce il corso nella lista risultato.
*/
list ricercaGenericaLista(list l, int sel,string str){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }
  list result=newList();
  Corso temp;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->c;
    switch(sel){
      case 0://Ricerca per ID
        if(strcmp(getIDCorso(temp), str)==0){
          insertList(result, 0, temp);
        }
        break;
      case 1://Ricerca per Nome
        if(strcmp(getNomeCorso(temp), str)==0){
          insertList(result, 0, temp);
        }
        break;
    }
    curr = curr->next;
  }
  return result;
}
/*
•  Funzione: ricercaData
•  -----------------------------------
•  Cerca corsi che si svolgono in una data specifica.
*
•  Parametri:
*   l: lista in cui cercare.
*   data: data da cercare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   data deve essere una data valida.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente i corsi della data specificata.
*   La lista originale rimane invariata.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota.
•  - Crea una nuova lista per i risultati.
•  - Scorre tutta la lista originale.
•  - Per ogni corso, confronta la data con quella cercata.
•  - Se corrisponde, inserisce il corso nella lista risultato.
*/
list ricercaData(list l, Data data){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }
  list result=newList();
  Corso temp;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->c;
    if(confrontaData(data,getDataCorso(temp))==0){
      insertList(result, 0, temp);
    }
    curr= curr->next;
  }
  return result;
}
/*
•  Funzione: ricercaMese
•  -----------------------------------
•  Cerca corsi che si svolgono in un mese specifico.
*
•  Parametri:
*   l: lista in cui cercare.
*   mm: mese da cercare (1-12).
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   mm deve essere un valore tra 1 e 12.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente i corsi del mese specificato.
*   La lista originale rimane invariata.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota.
•  - Crea una nuova lista per i risultati.
•  - Scorre tutta la lista originale.
•  - Per ogni corso, confronta il mese della data con quello cercato.
•  - Se corrisponde, inserisce il corso nella lista risultato.
*/
list ricercaMese(list l, int mm){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }
  list result=newList();
  Corso temp;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->c;
    if(mm==getMese(getDataCorso(temp))){
      insertList(result, 0, temp);
    }
    curr= curr->next;
  }
  return result;
}
/*
•  Funzione: lezioniInEvidenza
•  -----------------------------------
•  Trova i tre corsi con il maggior numero di partecipanti.
*
•  Parametri:
*   l: lista in cui cercare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente i primi tre corsi per numero di partecipanti.
*   La lista è ordinata dal primo al terzo posto.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota.
•  - Inizializza variabili per tracciare i primi tre corsi.
•  - Scorre tutta la lista confrontando il numero di partecipanti.
•  - Mantiene una classifica dei primi tre corsi.
•  - Inserisce i risultati in una nuova lista nell'ordine corretto.
*/
list lezioniInEvidenza(list l){
  if(l == NULL){
    printf("Lista vuota\n");
    return NULL;
  }
  list classifica=newList();
  int primo=0, secondo=0, terzo=0;
  Corso primoC=NULL;
  Corso secondoC=NULL;
  Corso terzoC=NULL;

  Corso temp;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->c;
    if(getNumPartecipantiCorso(temp)>primo){
      terzo = secondo;
      terzoC = secondoC;
      secondo = primo;
      secondoC = primoC;
      primo = getNumPartecipantiCorso(temp);
      primoC = temp;
      }else if(getNumPartecipantiCorso(temp)>secondo){
        terzo = secondo;
        terzoC = secondoC;
        secondo = getNumPartecipantiCorso(temp);
        secondoC = temp;
        }else if(getNumPartecipantiCorso(temp)>terzo){
          terzo = getNumPartecipantiCorso(temp);
          terzoC = temp;
          }
    curr = curr->next;
  }


  if(terzoC!=NULL){
    insertList(classifica, 0, terzoC);
  }
  if(secondoC!=NULL){
    insertList(classifica, 0, secondoC);
  }
  if(primoC!=NULL){
    insertList(classifica, 0, primoC);
  }
  return classifica;
}
/*
•  Funzione: ricercaOrario
•  -----------------------------------
•  Cerca corsi che si svolgono a un orario specifico.
*
•  Parametri:
*   l: lista in cui cercare.
*   h: ora da cercare.
*   m: minuti da cercare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   h deve essere tra 0 e 23.
*   m deve essere tra 0 e 59.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente i corsi dell'orario specificato.
*   La lista originale rimane invariata.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota.
•  - Crea un oggetto Orario con i parametri forniti.
•  - Crea una nuova lista per i risultati.
•  - Scorre tutta la lista originale.
•  - Per ogni corso, confronta l'orario con quello cercato.
•  - Se corrisponde, inserisce il corso nella lista risultato.
*/
list ricercaOrario(list l, int h,int m){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }
	list result=newList();
  Orario o=creaOrario(h,m);
  if(o==NULL){
    printf("Errore nella creazione di orario\n");
    exit(1);
  }
  Corso temp;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->c;
    if(confrontaOrario(o,getOrario(temp))==0){
      insertList(result, 0, temp);
    }
    curr= curr->next;
  }
  return result;
}
/*
•  Funzione: stampaLista
•  -----------------------------------
•  Stampa tutti i corsi presenti nella lista in formato completo.
*
•  Parametri:
*   l: lista da stampare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*
•  Post-condizione:
*   Tutti i corsi vengono stampati a video.
*   Se la lista è vuota, viene stampato un messaggio appropriato.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota o non inizializzata.
•  - Scorre tutti i nodi della lista.
•  - Per ogni corso, chiama stampaCorso per visualizzarlo.
•  - Stampa una riga vuota alla fine.
*/
void stampaLista(list l) {
  if (l == NULL || l->first == NULL) {
    printf("La lista è vuota o non inizializzata.\n");
    return;
  }

  struct node* curr = l->first;
  int i=0;
  while (curr != NULL) {
    //printf("Corso %d:\n", i);
      stampaCorso(curr->c);
      curr = curr->next;
      i++;
    }
  printf("\n");
}
/*
•  Funzione: stampaListaEssenziale
•  -----------------------------------
•  Stampa i corsi in formato tabellare compatto con solo le informazioni essenziali.
*
•  Parametri:
*   l: lista da stampare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*
•  Post-condizione:
*   I corsi vengono stampati in formato tabellare con ID, Nome, Data e Orario.
*   Se la lista è vuota, viene stampato un messaggio appropriato.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota o non inizializzata.
•  - Stampa l'intestazione della tabella.
•  - Scorre tutti i nodi della lista.
•  - Per ogni corso, chiama stampaCorsoCompatta per visualizzarlo.
•  - Stampa una riga vuota alla fine.
*/
void stampaListaEssenziale(list l) {
  if (l == NULL || l->first == NULL) {
    printf("La lista è vuota o non inizializzata.\n");
    return;
  }
  printf("%-8s %-12s %-12s %s\n", "ID", "Nome", "Data", "Orario");
  struct node* curr = l->first;
  int i=0;
  while (curr != NULL) {
    //printf("Corso %d:\n", i);
      stampaCorsoCompatta(curr->c);
      curr = curr->next;
      i++;
    }
  printf("\n");
}
/*
•  Funzione: scriviFileCorso
•  -----------------------------------
•  Salva tutti i corsi della lista nel file "corsi.txt".
*
•  Parametri:
*   l: lista da salvare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   Deve essere possibile creare/scrivere il file "corsi.txt".
*
•  Post-condizione:
*   Tutti i corsi vengono salvati nel file.
*   Il file viene chiuso correttamente.
*
•  Come funziona:
•  - Apre il file "corsi.txt" in modalità scrittura.
•  - Verifica che l'apertura sia avvenuta con successo.
•  - Scorre tutti i corsi della lista.
•  - Per ogni corso, chiama scriviCorso per salvarlo nel file.
•  - Chiude il file.
*/
void scriviFileCorso(list l){
  FILE *fp;
  fp=fopen("corsi.txt","w");
  if(fp==NULL){
    printf("Errore apertura file iscritti\n");
    exit(0);
  }
  Corso temp;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->c;
    scriviCorso(temp,fp);
    curr= curr->next;
  }
  fclose(fp);
}
/*
•  Funzione: getFirstCorso
•  -----------------------------------
•  Restituisce il primo corso della lista.
*
•  Parametri:
*   l: lista da cui estrarre il primo corso.
*
•  Pre-condizione:
*   l deve essere una lista valida e non vuota.
*
•  Post-condizione:
*   Restituisce il primo corso della lista o NULL se la lista è vuota.
*   La lista rimane invariata.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota o non inizializzata.
•  - Restituisce il corso contenuto nel primo nodo.
•  - Se la lista è vuota, stampa un messaggio e restituisce NULL.
*/
Corso getFirstCorso(list l){
  if (l == NULL || l->first == NULL) {
    printf("La lista è vuota o non inizializzata.\n");
    return NULL;
  }
  return l->first->c;
}
/*
•  Funzione: cancellaCorso
•  -----------------------------------
•  Cerca e rimuove un corso dalla lista usando il suo ID.
*
•  Parametri:
*   l: lista da cui rimuovere il corso.
*   IDCorso: ID del corso da rimuovere.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   IDCorso deve essere una stringa valida.
*
•  Post-condizione:
*   Il corso con l'ID specificato viene rimosso se trovato.
*   Restituisce 1 se il corso è stato rimosso, 0 altrimenti.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota o non inizializzata.
•  - Scorre la lista confrontando l'ID di ogni corso.
•  - Quando trova il corso corrispondente, chiama removeList per rimuoverlo.
•  - Restituisce 1 se la rimozione è avvenuta con successo, 0 altrimenti.
*/
int cancellaCorso(list l,string IDCorso){
  if(l==NULL || l->first==NULL){
    printf("La lista è vuota o non inizializzata.\n");
    return 0;
  }
  Corso temp;
  int i=0;
  struct node* curr = l->first;
  while(curr != NULL){
    temp = curr->c;
    if(strcmp(getIDCorso(temp), IDCorso) == 0){
      if(removeList(l,i)==0){
        //errore nella cancellazione
        return 0;
        }
        return 1;
    }
    curr = curr->next;
    i++;
  }
  return 0;
}
/*
•  Funzione: scriviLezioniInEvidenza
•  -----------------------------------
•  Scrive i corsi in evidenza in un file con formato specifico.
*
•  Parametri:
*   l: lista dei corsi in evidenza da scrivere.
*   fp: puntatore al file aperto in scrittura.
*
•  Pre-condizione:
*   fp deve essere un file aperto in modalità scrittura.
*   l può essere NULL o vuota.
*
•  Post-condizione:
*   I corsi vengono scritti nel file con formato: ID Nome Data NumPartecipanti.
*   Se la lista è vuota, scrive un messaggio appropriato.
*
•  Come funziona:
•  - Verifica se la lista è vuota o non inizializzata.
•  - Se vuota, scrive un messaggio nel file e termina.
•  - Altrimenti scorre tutti i corsi della lista.
•  - Per ogni corso, scrive ID, nome, data e numero partecipanti nel file.
*/
void scriviLezioniInEvidenza(list l, FILE *fp){
  if(l==NULL || l->first==NULL){
    fprintf(fp,"Non ci sono corsi in evidenza");
    return;
  }
  Corso temp;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->c;
    fprintf(fp,"%s %s %d/%d/%d %d\n",getIDCorso(temp),getNomeCorso(temp),getGiorno(getDataCorso(temp)),getMese(getDataCorso(temp)),getAnno(getDataCorso(temp)),getNumPartecipantiCorso(temp));
    //scriviCorso(temp,fp);
    curr= curr->next;
  }
}