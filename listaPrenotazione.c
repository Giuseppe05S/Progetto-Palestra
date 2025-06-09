//file liste.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaPrenotazione.h"
#include "prenotazione.h"
#include "data.h"


struct c_listP {
    struct node *first;
    int size;
};
struct node{
    Prenotazione p;
    struct node *next;
};
//Prototipi dichiarati in quanto chiamati
//prima di essere implementati
static struct node* insertNode(struct node* l, int pos, Prenotazione val);
static struct node* removeNode(struct node* l, int pos);

/*
•  Funzione: newListPrenotati
•  -------------------------
•  Crea una nuova lista vuota di prenotazioni.
*
•  Parametri:
*   Nessun parametro.
*
•  Pre-condizione:
*   Nessuna.
*
•  Post-condizione:
*   Viene allocata in memoria una nuova lista vuota di prenotazioni.
*   La lista ha first = NULL e size = 0.
*
•  Come funziona:
•  - Alloca memoria per la struttura c_listP.
•  - Inizializza il puntatore first a NULL.
•  - Inizializza la dimensione size a 0.
*/
listP newListPrenotati(void){
    struct c_listP *l;
    l = malloc(sizeof(struct c_listP));
    if (l != NULL){
        l->first = NULL;
        l->size = 0;
    }
    return l;
}
/*
•  Funzione: insertListPrenotati
•  ------------------------------
•  Inserisce una prenotazione in una posizione specifica della lista.
*
•  Parametri:
*   l: lista di prenotazioni dove inserire.
*   pos: posizione dove inserire (0 = testa della lista).
*   val: prenotazione da inserire.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   pos deve essere >= 0 e <= dimensione della lista.
*   val deve essere una prenotazione valida.
*
•  Post-condizione:
*   La prenotazione viene inserita nella posizione specificata.
*   La dimensione della lista viene incrementata di 1.
*   Gli elementi successivi vengono spostati in avanti.
*
•  Come funziona:
•  - Chiama la funzione ausiliaria insertNode per inserire il nodo.
•  - Aggiorna il puntatore al primo elemento se necessario.
•  - Incrementa la dimensione della lista.
*/
int insertListPrenotati(listP l, int pos, Prenotazione val){
    struct node* tmp = insertNode(l->first, pos, val); // Chiama insertNode per inserire un nuovo nodo nella lista
    if(tmp == NULL)
      return 0; // Se insertNode restituisce NULL, l'inserimento è fallito (es. errore di allocazione memoria), restituisce 0
    l->first = tmp; // Aggiorna il puntatore al primo nodo della lista con il possibile nuovo primo nodo (se inserito in testa)
    l->size++; // Incrementa la dimensione della lista di uno

    return 1; // Restituisce 1 per indicare che l'inserimento è avvenuto con successo
}
/*
•  Funzione: insertNode (statica)
•  -------------------------------
•  Funzione ausiliaria per inserire un nuovo nodo nella lista collegata.
*
•  Parametri:
*   l: puntatore al primo nodo della lista.
*   pos: posizione dove inserire il nuovo nodo.
*   val: prenotazione da inserire nel nuovo nodo.
*
•  Pre-condizione:
*   pos deve essere >= 0.
*   val deve essere una prenotazione valida.
*
•  Post-condizione:
*   Un nuovo nodo viene inserito nella posizione specificata.
*   I collegamenti tra i nodi vengono aggiornati correttamente.
*
•  Come funziona:
•  - Alloca memoria per il nuovo nodo.
•  - Se pos = 0, inserisce in testa alla lista.
•  - Altrimenti scorre fino alla posizione desiderata.
•  - Aggiorna i puntatori per inserire il nuovo nodo.
*/
static struct node* insertNode(struct node* l, int pos, Prenotazione val){
    struct node *new, *prec = l; // 'new' è il nuovo nodo da inserire, 'prec' è il puntatore al nodo precedente nella lista
    int i = 0;

    new = malloc(sizeof(struct node)); // Alloca memoria per il nuovo nodo
    if (!new)
      return NULL; // Se l'allocazione fallisce, restituisce NULL

    new->p = val; // Imposta il valore del nuovo nodo

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
•  Funzione: removeListPrenotati
•  ------------------------------
•  Rimuove una prenotazione dalla posizione specificata nella lista.
*
•  Parametri:
*   l: lista di prenotazioni da cui rimuovere.
*   pos: posizione dell'elemento da rimuovere (0 = primo elemento).
*
•  Pre-condizione:
*   l deve essere una lista valida e non vuota.
*   pos deve essere >= 0 e < dimensione della lista.
*
•  Post-condizione:
*   L'elemento nella posizione specificata viene rimosso.
*   La dimensione della lista viene decrementata di 1.
*   Gli elementi successivi vengono spostati indietro.
*
•  Come funziona:
•  - Verifica che la lista sia valida e non vuota.
•  - Chiama la funzione ausiliaria removeNode per rimuovere il nodo.
•  - Decrementa la dimensione della lista.
*/
int removeListPrenotati(listP l, int pos){
    if (!l || l->first == NULL || l->size == 0) return 0; // Controlla se la lista è vuota o non inizializzata e restituisce 0 se vero

    l->first = removeNode(l->first, pos); // Chiama la funzione ausiliaria removeNode per rimuovere il nodo e aggiorna il puntatore al primo nodo
    l->size--; // Decrementa la dimensione della lista

    return 1; // Restituisce 1 per indicare che la rimozione è stata completata con successo
}
/*
•  Funzione: removeNode (statica)
•  -------------------------------
•  Funzione ausiliaria per rimuovere un nodo dalla lista collegata.
*
•  Parametri:
*   l: puntatore al primo nodo della lista.
*   pos: posizione del nodo da rimuovere.
*
•  Pre-condizione:
*   pos deve essere >= 0.
*   La lista deve contenere almeno pos+1 elementi.
*
•  Post-condizione:
*   Il nodo nella posizione specificata viene rimosso e deallocato.
*   I collegamenti tra i nodi vengono aggiornati correttamente.
*
•  Come funziona:
•  - Se pos = 0, rimuove il primo nodo.
•  - Altrimenti scorre fino al nodo precedente a quello da rimuovere.
•  - Aggiorna i puntatori per escludere il nodo dalla lista.
•  - Dealloca la memoria del nodo rimosso.
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
•  Funzione: reverseListPrenotazioni
•  ----------------------------------
•  Crea una nuova lista con le prenotazioni in ordine inverso.
*
•  Parametri:
*   l: lista di prenotazioni da invertire.
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
•  - Inserisce ogni elemento in testa alla nuova lista.
•  - Termina il programma se si verifica un errore di inserimento.
*/
listP reverseListPrenotazioni(listP l){
  listP rev=newListPrenotati();
  Prenotazione temp;
  struct node* curr = l->first;

  while(curr != NULL){
    temp = curr->p;
    if(insertListPrenotati(rev, 0, temp) == 0){
      printf("Errore nell'inserimento\n");
      exit(1);
    }
    curr = curr->next;
  }
  return rev;
}
/*
•  Funzione: ricercaListaPrenotati
•  --------------------------------
•  Cerca prenotazioni nella lista in base a criteri specificati.
*
•  Parametri:
*   l: lista di prenotazioni in cui cercare.
*   sel: criterio di ricerca (0=ID Cliente, 1=ID Corso, 2=ID Prenotazione).
*   str: stringa da cercare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   sel deve essere 0, 1 o 2.
*   str deve essere una stringa valida.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente solo le prenotazioni che corrispondono al criterio.
*   La lista originale rimane invariata.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota.
•  - Crea una nuova lista per i risultati.
•  - Scorre tutti gli elementi della lista originale.
•  - Confronta il campo specificato con la stringa di ricerca.
•  - Inserisce le prenotazioni corrispondenti nella lista risultato.
*/
listP ricercaListaPrenotati(listP l, int sel,string str){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }
  listP result = newListPrenotati();
  Prenotazione temp;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->p;
    switch(sel){
      case 0://Ricerca per ID Cliente
        if(strcmp(getIDClientePrenotazione(temp), str)==0){
          insertListPrenotati(result, 0, temp);
        }
        break;
      case 1://Ricerca per ID Corso
        if(strcmp(getIDCorsoPrenotazione(temp), str)==0){
          insertListPrenotati(result, 0, temp);
        }
        break;
      case 2://Ricerca per ID Prenotazione
        if(strcmp(getIDPrenotazione(temp), str)==0){
          insertListPrenotati(result, 0, temp);
        }
        break;
    }
    curr = curr->next;
  }
  return result;
}
/*
•  Funzione: cancellaPrenotazione
•  -------------------------------
•  Cancella una specifica prenotazione identificata da ID prenotazione e ID cliente.
*
•  Parametri:
*   l: lista di prenotazioni da cui cancellare.
*   IDPrenotazione: ID della prenotazione da cancellare.
*   IDCliente: ID del cliente che ha effettuato la prenotazione.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   IDPrenotazione e IDCliente devono essere stringhe valide.
*
•  Post-condizione:
*   La prenotazione corrispondente viene rimossa dalla lista se trovata.
*   La dimensione della lista viene decrementata se la cancellazione avviene.
*
•  Come funziona:
•  - Scorre la lista cercando una prenotazione con gli ID specificati.
•  - Confronta sia l'ID prenotazione che l'ID cliente.
•  - Se trova una corrispondenza, rimuove l'elemento dalla posizione corrente.
•  - Tiene traccia della posizione durante lo scorrimento.
*/
int cancellaPrenotazione(listP l,string IDPrenotazione,string IDCliente){
  Prenotazione temp;
  int i=0;
  struct node* curr = l->first;
  while(curr != NULL){
    temp = curr->p;
    if((strcmp(getIDPrenotazione(temp), IDPrenotazione) == 0)&&(strcmp(getIDClientePrenotazione(temp), IDCliente)==0)){
      if(removeListPrenotati(l,i)==0){
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
•  Funzione: cancellaPrenotazioneDi
•  ---------------------------------
•  Cancella tutte le prenotazioni associate a un cliente o a un corso specifico.
*
•  Parametri:
*   l: lista di prenotazioni da cui cancellare.
*   sel: criterio di cancellazione (0=tutte le prenotazioni di un cliente, 1=tutte le prenotazioni di un corso).
*   ID: ID del cliente o del corso.
*
•  Pre-condizione:
*   l deve essere una lista valida e non vuota.
*   sel deve essere 0 o 1.
*   ID deve essere una stringa valida.
*
•  Post-condizione:
*   Tutte le prenotazioni corrispondenti al criterio vengono rimosse.
*   La dimensione della lista viene aggiornata correttamente.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota.
•  - Scorre la lista mantenendo riferimenti al nodo corrente e successivo.
•  - Confronta l'ID appropriato in base al criterio selezionato.
•  - Rimuove gli elementi corrispondenti, gestendo correttamente gli indici.
•  - Conta gli elementi cancellati.
*/
int cancellaPrenotazioneDi(listP l,int sel,string ID){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }
  int elementiCancellati=0;
  Prenotazione temp;
  int i=0;
  struct node* curr = l->first;
  struct node* next;
  while(curr != NULL){
    temp = curr->p;
    // Salva il puntatore al nodo successivo PRIMA di eventualmente cancellare
    next = curr->next;
    switch(sel){
      case 0://Cancella tutte le prenotazioni di un cliente
        if(strcmp(getIDClientePrenotazione(temp), ID)==0){
          removeListPrenotati(l,i);
          /*quando rimuovo un elemento dalla lista, tutti gli elementi vengono scalati,
          senza decrementare i, mi ritroverei a saltare alcuni elementi della lista
          */
          elementiCancellati++;
        }else i++;//incremento solo se non cancello
        break;
      case 1://Cancella tutte le prenotazioni di un corso
        if(strcmp(getIDCorsoPrenotazione(temp), ID)==0){
          removeListPrenotati(l,i);
          elementiCancellati++;
        }else i++; //incremento solo se non cancello
        break;
    }
    curr = next;
  }
  return elementiCancellati;
}
/*
•  Funzione: getFirstPrenotazione
•  -------------------------------
•  Restituisce la prima prenotazione della lista senza rimuoverla.
*
•  Parametri:
*   l: lista di prenotazioni da cui ottenere il primo elemento.
*
•  Pre-condizione:
*   l deve essere una lista valida e non vuota.
*
•  Post-condizione:
*   La lista rimane invariata.
*   Viene restituita la prima prenotazione.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota.
•  - Accede direttamente al primo nodo della lista.
•  - Restituisce la prenotazione contenuta nel primo nodo.
*/
Prenotazione getFirstPrenotazione(listP l){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }
  return l->first->p;
}
/*
•  Funzione: isEmptyPrenotazione
•  ------------------------------
•  Verifica se la lista di prenotazioni è vuota.
*
•  Parametri:
*   l: lista di prenotazioni da verificare.
*
•  Pre-condizione:
*   Nessuna (gestisce anche liste NULL).
*
•  Post-condizione:
*   La lista rimane invariata.
*
•  Come funziona:
•  - Controlla se il puntatore alla lista è NULL.
•  - Controlla se il primo elemento della lista è NULL.
*/
int isEmptyPrenotazione(listP l){
  if (l == NULL||l->first == NULL){
    return 1;
  }
}
/*
•  Funzione: ricercaDataPrenotazione
•  ----------------------------------
•  Cerca e stampa tutte le prenotazioni effettuate in un mese specifico.
*
•  Parametri:
*   l: lista di prenotazioni in cui cercare.
*   mm: mese da cercare (1-12).
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   mm deve essere compreso tra 1 e 12.
*
•  Post-condizione:
*   Vengono stampate tutte le prenotazioni del mese specificato.
*   La lista rimane invariata.
*
•  Come funziona:
•  - Verifica che la lista non sia vuota.
•  - Scorre tutti gli elementi della lista.
•  - Confronta il mese di ogni prenotazione con quello cercato.
•  - Stampa le prenotazioni corrispondenti.
•  - Tiene traccia se è stata trovata almeno una corrispondenza.
*/
int ricercaDataPrenotazione(listP l, int mm){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }

  Prenotazione temp;
  int trovato=0;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->p;
    if(mm==getMese(getDataPrenotazione(temp))){
      stampaPrenotazione(temp);
      trovato = 1;
    }
    curr= curr->next;
  }
  return trovato;
}

/*
•  Funzione: stampaListaPrenotazioni
•  ----------------------------------
•  Stampa tutte le prenotazioni presenti nella lista.
*
•  Parametri:
*   l: lista di prenotazioni da stampare.
*
•  Pre-condizione:
*   l può essere una lista valida o NULL.
*
•  Post-condizione:
*   Tutte le prenotazioni vengono stampate a video.
*   La lista rimane invariata.
*
•  Come funziona:
•  - Verifica se la lista è vuota o NULL.
•  - Se vuota, stampa un messaggio informativo.
•  - Altrimenti scorre tutti gli elementi della lista.
•  - Stampa ogni prenotazione utilizzando la funzione specifica.
•  - Aggiunge una riga vuota alla fine.
*/
void stampaListaPrenotazioni(listP l) {
  if (l == NULL || l->first == NULL) {
    printf("Non ci sono prenotazioni.\n");
    return;
  }

  struct node* curr = l->first;
  int i=0;
  while (curr != NULL) {
    //printf("Corso %d:\n", i);
      stampaPrenotazione(curr->p);
      curr = curr->next;
      i++;
    }
  printf("\n");
}
/*
•  Funzione: scriviFilePrenotazione
•  ---------------------------------
•  Salva tutte le prenotazioni della lista in un file di testo.
*
•  Parametri:
*   l: lista di prenotazioni da salvare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   Deve essere possibile creare/scrivere il file "prenotazioni.txt".
*
•  Post-condizione:
*   Tutte le prenotazioni vengono scritte nel file "prenotazioni.txt".
*   Il file viene chiuso correttamente.
*   La lista rimane invariata.
*
•  Come funziona:
•  - Apre il file "prenotazioni.txt" in modalità scrittura.
•  - Verifica che l'apertura sia avvenuta con successo.
•  - Scorre tutti gli elementi della lista.
•  - Scrive ogni prenotazione nel file utilizzando la funzione specifica.
•  - Chiude il file.
*/
void scriviFilePrenotazione(listP l){
  FILE *fp;
  fp=fopen("prenotazioni.txt","w");
  if(fp==NULL){
    printf("Errore apertura file iscritti\n");
    exit(0);
  }
  Prenotazione temp;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->p;
    scriviPrenotazione(temp,fp);
    curr= curr->next;
  }
  fclose(fp);
}
