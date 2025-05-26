//file liste.h
#ifndef LISTE_H
#define LISTE_H

#include "corso.h"

// Forward declaration
typedef struct corso *Corso;
typedef struct c_list *list;


list newList(void); //Crea una nuova lista vuota e restituisce la lista creata;
int insertList(list l, int pos, Corso val);
int removeList(list l, int pos);
void stampaLista(list l);
list reverseList(list l);
list ricercaGenericaLista(list l, int sel,string str);
int isEmpty(list l);
list ricercaData(list l, Data data);
list ricercaOrario(list l, int h,int m);
void lezioniInEvidenza(list l);
void scriviFileCorso(list l);
Corso getFirstCorso(list l);
list ricercaMese(list l, int mm);
int cancellaCorso(list l,string IDCorso);
void stampaListaEssenziale(list l);

/*
static struct node* insertNode(struct node* l, int pos, Corso val);
static struct node* removeNode(struct node* l, int pos);
*/
#endif