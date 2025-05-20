#ifndef LISTA_PRENOTAZIONE_H
#define LISTA_PRENOTAZIONE_H

#include "listaPrenotazione.h"
#include "data.h"

// Forward declaration
typedef struct prenotazione *Prenotazione;
typedef struct c_list *listP;


listP newListPrenotati(void); //Crea una nuova lista vuota e restituisce la lista creata;
int insertListPrenotati(listP l, int pos, Prenotazione val);
int removeListPrenotati(listP l, int pos);
listP reverseListPrenotazioni(listP l);

void stampaListaPrenotazioni(listP l);

//int ricercaGenericaLista(list l, int sel,string str);
int ricercaDataPrenotazione(listP l, Data data);
//int ricercaOrario(list l, int h,int m);
void scriviFilePrenotazione(listP l);

#endif