//
// Created by Giuseppe on 09/05/2025.
//

#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include "iscritto.h"
#include "utils.h"
#include <string.h>
//libreria per FNV-1a
#include <stdint.h>

// Definizione della struttura della tabella hash.

struct hash {
    int size;              // Dimensione della tabella hash.
    Iscritto *table;   // Puntatore a un array di puntatori a 'item'.
};

// Funzione per creare una nuova tabella hash.
hashtable newHashtable(int size) {
  int i;
  hashtable h = (struct hash *) malloc (sizeof(struct hash));
  if(h == NULL){
    printf("Errore di Allocazione\n");
    exit(1);
  }
  h->size = size;
  h->table = (Iscritto *) calloc (size,sizeof(Iscritto));

  // for(i=0; i<size; i++) {
  // h->table[i] = NULL;
  // }

  return h;
}
// Funzione per inserire un elemento in una tabella hash.
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

// Funzione per eliminare un elemento da una tabella hash basandosi sulla chiave fornita.
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

// Funzione per distruggere (eliminare completamente) una tabella hash.
void destroyHashtable(hashtable h) {
  int i;
  for(i=0; i < h->size; i++) {
    deleteList(h->table[i]);
  }
  free(h->table);
  free(h);
  return;
}

// Versione iterativa di deleteList per evitare l'overflow dello stack su liste lunghe.
static void deleteList(Iscritto p) {
  if(p == NULL) 
    return;
  deleteList(getNext(p));
  free(p);
  return;
}

//Funzione di ricerca in base alla chiave
Iscritto hashSearch(hashtable h, string key) {
  if (h == NULL || key == NULL) 
    return NULL;
  
  int idx = hashFun(key, h->size);         // Calcola l'indice nella tabella
  Iscritto curr = h->table[idx];       // Inizia dalla testa della lista
  while (curr != NULL) {
    if (strcmp(getID(curr), key) == 0) {
      return curr;                     // Trovato!
    }
    curr = getNext(curr);                   // Vai al prossimo nodo
  }
  return NULL;  // Non trovato
}
void stampaHash(hashtable h) {
  if(h == NULL){
    printf("Tabella vuota\n");
    return;
  }
  int i;
  for(i=0; i < h->size; i++) {
    Iscritto curr = h->table[i];
    if (curr != NULL) {
      printf("Indice %d:\n", i);
    }
    while (curr != NULL) {
      // Usa le funzioni di accesso (getter) per rispettare l'information hiding
      stampaCliente(curr);
      // Aggiungi altri campi se necessari, es. nome, data, ecc.
      curr = getNext(curr);
    }
  }

}
// Funzione hash che calcola l'indice basato sulla chiave e sulla dimensione della tabella.
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

