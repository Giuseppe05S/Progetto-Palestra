//file liste.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaPrenotazione.h"
#include "prenotazione.h"
#include "data.h"


struct c_list {
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

listP newListPrenotati(void){
    struct c_list *l;
    l = malloc(sizeof(struct c_list));
    if (l != NULL){
        l->first = NULL;
        l->size = 0;
    }
    return l;
}

int insertListPrenotati(listP l, int pos, Prenotazione val){
    struct node* tmp = insertNode(l->first, pos, val); // Chiama insertNode per inserire un nuovo nodo nella lista
    if(tmp == NULL)
      return 0; // Se insertNode restituisce NULL, l'inserimento è fallito (es. errore di allocazione memoria), restituisce 0
    l->first = tmp; // Aggiorna il puntatore al primo nodo della lista con il possibile nuovo primo nodo (se inserito in testa)
    l->size++; // Incrementa la dimensione della lista di uno

    return 1; // Restituisce 1 per indicare che l'inserimento è avvenuto con successo
}

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
int removeListPrenotati(listP l, int pos){
    if (!l || l->first == NULL || l->size == 0) return 0; // Controlla se la lista è vuota o non inizializzata e restituisce 0 se vero

    l->first = removeNode(l->first, pos); // Chiama la funzione ausiliaria removeNode per rimuovere il nodo e aggiorna il puntatore al primo nodo
    l->size--; // Decrementa la dimensione della lista

    return 1; // Restituisce 1 per indicare che la rimozione è stata completata con successo
}

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
listP reverseListPrenotazioni(list l){
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
// da controllare se serve
/*int ricercaGenericaLista(listP l, int sel,string str){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }

  int trovato=0;
  Prenotazione temp;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->p;
    switch(sel){
      case 0://Ricerca per ID Prenotazione
        if(strcmp(getIDCorso(temp), str)==0){
          stampaPrenotazione(temp);
          trovato = 1;
        }
        break;
      case 1://Ricerca per ID per Iscritto
        if(strcmp(getNomeCorso(temp), str)==0){
          stampaCorso(temp);
          trovato = 1;
        }
        break;
    }
    curr = curr->next;
  }
  return trovato;
}
*/
int ricercaDataPrenotazione(listP l, Data data){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }

  Prenotazione temp;
  int trovato=0;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->p;
    if(confrontaData(data,getDataPrenotazione(temp))==0){
      stampaPrenotazione(temp);
      trovato = 1;
    }
    curr= curr->next;
  }
  return trovato;
}
//non dovrebbe servire
/*int ricercaOrario(listP l, int h,int m){
  if(l == NULL){
    printf("Lista vuota\n");
    return 0;
  }
  Orario o=creaOrario(h,m);
  if(o==NULL){
    printf("Errore nella creazione di orario\n");
    exit(1);
  }
  Corso temp;
  int trovato=0;
  struct node* curr = l->first;
  while(curr!=NULL){
    temp = curr->c;
    if(confrontaOrario(o,getOrario(temp))==0){
      stampaCorso(temp);
      trovato = 1;
    }
    curr= curr->next;
  }
  return trovato;
}
*/
// Stampa tutti gli elementi della lista di corsi
void stampaListaPrenotazioni(listP l) {
  if (l == NULL || l->first == NULL) {
    printf("La lista è vuota o non inizializzata.\n");
    return;
  }

  struct node* curr = l->first;
  int i=0;
  printf("==============================\n");
  printf("\tELENCO PRENOTAZIONI\n");
  printf("==============================\n");
  while (curr != NULL) {
    //printf("Corso %d:\n", i);
      stampaPrenotazione(curr->p);
      curr = curr->next;
      i++;
    }
  printf("\n");
}
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
