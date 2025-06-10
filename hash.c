//
// Created by Giuseppe on 09/05/2025.
//
//#include "utils.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>    //libreria per FNV-1a

// Definizione della struttura della tabella hash.

struct hash {
    int size;              // Dimensione della tabella hash.
    Iscritto *table;   // Puntatore a un array di puntatori a iscritto.
};

//Prototipi dichiarati in quanto chiamati
//prima di essere implementati
static void deleteList(Iscritto p);
static int hashFun(const char *key, int size);
static uint32_t fnv1aHash32(const char *key);


/*
•  Funzione: newHashtable
•  -----------------------------------
•  Crea e inizializza una nuova tabella hash.
*
•  Parametri:
*   size: dimensione della tabella hash da creare.
*
•  Pre-condizione:
*   size deve essere un valore positivo maggiore di 0.
*
•  Post-condizione:
*   Viene allocata e restituita una nuova tabella hash vuota.
*   Tutti gli slot della tabella sono inizializzati a NULL.
*
•  Come funziona:
•  - Alloca memoria per la struttura hashtable.
•  - Imposta la dimensione della tabella.
•  - Alloca memoria per l'array di puntatori agli iscritti.
•  - Inizializza tutti i puntatori a NULL usando calloc.
•  - Restituisce il puntatore alla nuova tabella hash.
*/
hashtable newHashtable(int size) {
  int i;
  hashtable h = (struct hash *) malloc (sizeof(struct hash));
  if(h == NULL){
    printf("Errore di Allocazione\n");
    exit(1);
  }
  h->size = size;
  h->table = (Iscritto *) calloc (size,sizeof(Iscritto));

  return h;
}
/*
•  Funzione: insertHash
•  -----------------------------------
•  Inserisce un nuovo elemento nella tabella hash.
*
•  Parametri:
*   h: tabella hash in cui inserire l'elemento.
*   elem: elemento iscritto da inserire.
*
•  Pre-condizione:
*   h deve essere una tabella hash valida.
*   elem deve essere un iscritto valido con ID univoco.
*
•  Post-condizione:
*   L'elemento viene inserito in testa alla lista di collisione.
*   Restituisce 1 se l'inserimento è avvenuto con successo.
*   Restituisce 0 se l'elemento esiste già (stesso ID).
*
•  Come funziona:
•  - Calcola l'indice hash usando la funzione hashFun sull'ID.
•  - Scorre la lista di collisione per verificare duplicati.
•  - Se non trova duplicati, inserisce in testa alla lista.
•  - Aggiorna il puntatore della tabella hash.
*/
int insertHash(hashtable h, Iscritto elem) {
  int idx;
  Iscritto head, curr;
  idx = hashFun(getID(elem), h->size);
  curr = head = h->table[idx];
  while(curr) {
    if(strcmp(getID(curr), getID(elem))==0 )
      return (0);
    curr = getNext(curr);
  }
  setNext(elem, head);        // Inserimento in testa alla lista
  h->table[idx] = elem;
  return (1);
}

/*
•  Funzione: hashDelete
•  -----------------------------------
•  Elimina un elemento dalla tabella hash basandosi sulla chiave.
*
•  Parametri:
*   h: tabella hash da cui eliminare l'elemento.
*   key: chiave (ID) dell'elemento da eliminare.
*
•  Pre-condizione:
*   h deve essere una tabella hash valida.
*   key deve essere una stringa valida non NULL.
*
•  Post-condizione:
*   L'elemento viene rimosso dalla lista di collisione.
*   I collegamenti della lista vengono aggiornati correttamente.
*   Restituisce il puntatore all'elemento eliminato o NULL se non trovato.
*
•  Come funziona:
•  - Calcola l'indice hash della chiave.
•  - Scorre la lista di collisione mantenendo traccia dell'elemento precedente.
•  - Se trova l'elemento, aggiorna i collegamenti per rimuoverlo.
•  - Gestisce separatamente il caso di eliminazione della testa.
•  - Restituisce il puntatore all'elemento eliminato.
*/
Iscritto hashDelete(hashtable h, string key) {
  int idx;
  Iscritto prev, curr, head, temp;
  idx = hashFun(key, h->size);
  prev = curr = head = h->table[idx];
  while(curr){
    if( !strcmp(getID(curr), key) ) {
      if(curr == head)
        h->table[idx] = getNext(curr);
      else
        setNext(prev, getNext(curr));
      return(curr);
    }
    prev = curr;
    curr = getNext(curr);
  }
  return NULL;
}

/*
•  Funzione: destroyHashtable
•  -----------------------------------
•  Distrugge completamente una tabella hash liberando tutta la memoria.
*
•  Parametri:
*   h: tabella hash da distruggere.
*
•  Pre-condizione:
*   h deve essere una tabella hash valida.
*
•  Post-condizione:
*   Tutta la memoria allocata per la tabella e i suoi elementi viene liberata.
*   La tabella hash non è più utilizzabile dopo questa operazione.
*
•  Come funziona:
•  - Scorre tutti gli slot della tabella hash.
•  - Per ogni slot, elimina ricorsivamente tutta la lista di collisione.
•  - Libera la memoria dell'array della tabella.
•  - Libera la memoria della struttura hashtable principale.
*/
void destroyHashtable(hashtable h) {
  int i;
  for(i=0; i < h->size; i++) {
    deleteList(h->table[i]);
  }
  free(h->table);
  free(h);
  return;
}

/*
•  Funzione: deleteList (static)
•  -----------------------------------
•  Elimina ricorsivamente tutti i nodi di una lista collegata.
*
•  Parametri:
*   p: puntatore al primo nodo della lista da eliminare.
*
•  Pre-condizione:
*   p può essere NULL o puntare a una lista valida.
*
•  Post-condizione:
*   Tutti i nodi della lista vengono liberati dalla memoria.
*   La memoria di ogni nodo viene deallocata correttamente.
*
•  Come funziona:
•  - Caso base: se p è NULL, termina la ricorsione.
•  - Chiama ricorsivamente deleteList sul nodo successivo.
•  - Libera la memoria del nodo corrente.
•  - Implementazione ricorsiva che procede in post-ordine.
*/
static void deleteList(Iscritto p) {
  if(p == NULL)
    return;
  deleteList(getNext(p));
  free(p);
  return;
}

/*
•  Funzione: hashSearch
•  -----------------------------------
•  Cerca un elemento nella tabella hash basandosi sulla chiave.
*
•  Parametri:
*   h: tabella hash in cui cercare.
*   key: chiave (ID) dell'elemento da cercare.
*
•  Pre-condizione:
*   h deve essere una tabella hash valida o NULL.
*   key deve essere una stringa valida o NULL.
*
•  Post-condizione:
*   Restituisce il puntatore all'elemento trovato.
*   Restituisce NULL se l'elemento non esiste o i parametri sono invalidi.
*
•  Come funziona:
•  - Verifica la validità dei parametri di input.
•  - Calcola l'indice hash della chiave.
•  - Scorre la lista di collisione confrontando gli ID.
•  - Restituisce l'elemento se trovato, altrimenti NULL.
*/
Iscritto hashSearch(hashtable h, string key) {
  if (h == NULL || key == NULL) 
    return NULL;
  
  int idx = hashFun(key, h->size);         // Calcola l'indice nella tabella
  Iscritto curr = h->table[idx];           // Inizia dalla testa della lista
  while (curr != NULL) {
    if (strcmp(getID(curr), key) == 0) {
      return curr;         // Trovato!
    }
    curr = getNext(curr);  // Vai al prossimo nodo
  }
  return NULL;  // Non trovato
}
/*
•  Funzione: ricercaGenerica
•  -----------------------------------
•  Esegue una ricerca generica nella tabella hash per vari criteri.
*
•  Parametri:
*   h: tabella hash in cui cercare.
*   sel: selettore del tipo di ricerca (0=nome, 1=cognome, 2=durata).
*   str: stringa di ricerca o valore da confrontare.
*
•  Pre-condizione:
*   h deve essere una tabella hash valida.
*   sel deve essere 0, 1 o 2.
*   str deve essere una stringa valida.
*
•  Post-condizione:
*   Stampa tutti gli elementi che corrispondono al criterio di ricerca.
*   Restituisce 1 se trova almeno un elemento valido.
*   Restituisce -1 se trova elementi con abbonamento scaduto.
*   Restituisce 0 se non trova nessun elemento.
*
•  Come funziona:
•  - Scorre tutti gli slot della tabella hash.
•  - Per ogni slot non vuoto, applica il criterio di ricerca selezionato.
•  - Controlla lo stato dell'abbonamento per nome e cognome.
•  - Stampa i dettagli degli elementi trovati.
•  - Restituisce un codice di stato basato sui risultati.
*/
int ricercaGenerica(hashtable h, int sel, string str) {
  int trovato=0;
  for(int i=0;i<h->size; i++){
    if(h->table[i]!=NULL){

      Iscritto is=h->table[i];

      switch(sel){

      	case 0: // Ricerca per nome
          if(strcmp(getNome(is), str)==0){
            if(controlloAbbonamento(is)==0){
          	  stampaCliente(is);
          	  trovato=1;
              break;
            }else{
              trovato=-1;
            }
          }
          break;
      	case 1: // Ricerca per cognome
          if(strcmp(getCognome(is), str)==0){
            if(controlloAbbonamento(is)==0){
              stampaCliente(is);
              trovato=1;
              break;
            }else{
              trovato=-1;
            }
          }
          break;
        case 2: // Ricerca per durata abbonamento
          int durata=atoi(str);
          if(getDurata(is)==durata){
            stampaCliente(is);
            trovato=1;
          }
          break;
      }
    }
  }
  return trovato;
}
/*
•  Funzione: stampaHash
•  -----------------------------------
•  Stampa tutti gli elementi presenti nella tabella hash.
*
•  Parametri:
*   h: tabella hash da stampare.
*
•  Pre-condizione:
*   h può essere una tabella hash valida o NULL.
*
•  Post-condizione:
*   Vengono stampati tutti gli iscritti presenti nella tabella.
*   Se la tabella è vuota o NULL, stampa un messaggio appropriato.
*
•  Come funziona:
•  - Verifica se la tabella è NULL e stampa messaggio di errore.
•  - Scorre tutti gli slot della tabella hash.
•  - Per ogni slot, scorre la lista di collisione.
•  - Stampa i dettagli completi di ogni iscritto trovato.
•  - Aggiunge una riga vuota finale per formattazione.
*/
void stampaHash(hashtable h) {
  if(h == NULL){
    printf("Tabella vuota\n");
    return;
  }
  int i;
  for(i=0; i < h->size; i++) {
    Iscritto curr = h->table[i];
    while (curr != NULL) {
      stampaCliente(curr);
      curr = getNext(curr);
    }
  }
  printf("\n");
}
/*
•  Funzione: stampaHashMinima
•  -----------------------------------
•  Stampa una versione ridotta di tutti gli elementi della tabella hash.
*
•  Parametri:
*   h: tabella hash da stampare.
*
•  Pre-condizione:
*   h può essere una tabella hash valida o NULL.
*
•  Post-condizione:
*   Vengono stampati ID, cognome e nome di tutti gli iscritti.
*   La stampa include un'intestazione formattata.
*   Se la tabella è vuota, stampa un messaggio appropriato.
*
•  Come funziona:
•  - Verifica se la tabella è NULL e stampa messaggio di errore.
•  - Stampa un'intestazione formattata con separatori.
•  - Scorre tutti gli slot della tabella hash.
•  - Per ogni slot, scorre la lista di collisione.
•  - Stampa solo le informazioni essenziali di ogni iscritto.
*/
void stampaHashMinima(hashtable h) {
  if(h == NULL){
    printf("Tabella vuota\n");
    return;
  }
  printf("==============================\n");
  printf("%-8s %-15s %-15s\n","ID","Cognome","Nome");
  Iscritto curr;

  int i;
  for(i=0; i < h->size; i++) {
    curr = h->table[i];
    while (curr != NULL) {
      stampaMinimaCliente(curr);
      curr = getNext(curr);
    }
  }
  printf("\n");
}
/*
•  Funzione: scriviFileClienti
•  -----------------------------------
•  Scrive tutti gli iscritti della tabella hash su file di testo.
*
•  Parametri:
*   h: tabella hash contenente gli iscritti da salvare.
*
•  Pre-condizione:
*   h deve essere una tabella hash valida.
*   Deve essere possibile creare/scrivere il file "iscritti.txt".
*
•  Post-condizione:
*   Tutti gli iscritti vengono salvati nel file "iscritti.txt".
*   Il file viene chiuso correttamente dopo la scrittura.
*   Il programma termina in caso di errore di apertura file.
*
•  Come funziona:
•  - Apre il file "iscritti.txt" in modalità scrittura.
•  - Verifica l'apertura corretta del file ed esce in caso di errore.
•  - Scorre tutti gli slot della tabella hash.
•  - Per ogni slot, scorre la lista di collisione.
•  - Scrive ogni iscritto nel file usando la funzione scriviCliente.
•  - Chiude il file al termine delle operazioni.
*/
void scriviFileClienti(hashtable h){
  FILE *fp;
  fp=fopen("iscritti.txt","w");
  if(fp==NULL){
    printf("Errore apertura file iscritti\n");
    exit(0);
  }
  Iscritto curr;

  int i;
  for(i=0; i < h->size; i++) {
    curr = h->table[i];
    while (curr != NULL) {
      scriviCliente(curr,fp);
      curr = getNext(curr);
    }
  }
  fclose(fp);
}

/*
•  Funzione: hashFun (static)
•  -----------------------------------
•  Calcola l'indice hash per una chiave nella tabella hash.
*
•  Parametri:
*   key: stringa chiave per cui calcolare l'hash.
*   size: dimensione della tabella hash.
*
•  Pre-condizione:
*   key deve essere una stringa valida non NULL.
*   size deve essere un valore positivo maggiore di 0.
*
•  Post-condizione:
*   Restituisce un indice valido compreso tra 0 e size-1.
*   Lo stesso input produce sempre lo stesso output.
*
•  Come funziona:
•  - Utilizza l'algoritmo FNV-1a per calcolare un hash a 32 bit.
•  - Applica l'operazione modulo per mappare l'hash nell'intervallo [0, size-1].
•  - Garantisce una distribuzione uniforme degli indici.
*/
static int hashFun(const char *key, int size) {
    return fnv1aHash32(key) % size;
}

static uint32_t fnv1aHash32(const char *key) {
    uint32_t hash = 2166136261u;
    while (*key) {
        hash ^= (unsigned char)(*key);
        hash *= 16777619u;
        key++;
    }
    return hash;
}

