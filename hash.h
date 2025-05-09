//
// Created by Giuseppe on 09/05/2025.
//

#include "iscritto.h"

typedef struct hash* hashtable;

// Funzione per creare una nuova tabella hash.
hashtable newHashtable(int size);

// Funzione per inserire un elemento in una tabella hash.
int insertHash(hashtable h, Iscritto x);

// Funzione per eliminare un elemento da una tabella hash basandosi sulla chiave fornita.
Iscritto hashDelete(hashtable h, string key);

// Funzione per distruggere (eliminare completamente) una tabella hash.
void destroyHashtable(hashtable h);

//Funzione di ricerca in base alla chiave
Iscritto hashSearch(hashtable h, string key);

