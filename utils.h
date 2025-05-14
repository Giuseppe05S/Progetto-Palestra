//
// Created by Giuseppe on 28/04/2025.
//

#ifndef UTILS_H
#define UTILS_H

typedef char *string;

#include "liste.h"
#include "hash.h"
//aggiunte dall'ia
typedef struct hash* hashtable;
typedef struct c_list* list;
//.
//posizione typedef string

string generaIDCliente();
string generaIDCorso();
void caricaFileClienti(hashtable h);
void caricaFileCorso(list l);

#endif