#ifndef LISTA_PRENOTAZIONE_H
#define LISTA_PRENOTAZIONE_H

#include "listaPrenotazione.h"
#include "data.h"

// Forward declaration
typedef struct prenotazione *Prenotazione;
typedef struct c_listP *listP;
typedef char *string;

listP newListPrenotati(void); //Crea una nuova lista vuota e restituisce la lista creata;
int insertListPrenotati(listP l, int pos, Prenotazione val);
int removeListPrenotati(listP l, int pos);
listP reverseListPrenotazioni(listP l);
listP ricercaListaPrenotati(listP l, int sel,string str);//0 per Cliente e 1 per Corso
void stampaListaPrenotazioni(listP l);
int isEmptyPrenotazione(listP l);//1 se vuota, altrimenti 0
listP ricercaMesePrenotazione(listP l, int mm);
void scriviFilePrenotazione(listP l);
int cancellaPrenotazioneDi(listP l,int sel,string ID);//0 per Cliente e 1 per Corso
int cancellaPrenotazione(listP l,string IDCorso,string IDCliente);
Prenotazione getFirstPrenotazione(listP l);
int getSize(listP l);
#endif