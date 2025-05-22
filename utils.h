//
// Created by Giuseppe on 28/04/2025.
//

#ifndef UTILS_H
#define UTILS_H

typedef char *string;

// Forward declarations
typedef struct hash* hashtable;
typedef struct c_list* list;
typedef struct c_listP *listP;
//.
//posizione typedef string

string generaIDCliente();
string generaIDPrenotazione();
string generaIDCorso();
void caricaFileClienti(hashtable h);
void caricaFileCorso(list l);
void caricaFilePrenotazioni(listP l);
void pulisciSchermo();

#endif