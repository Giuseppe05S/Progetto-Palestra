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
int ricercaGenericaLista(list l, int sel,string str);
int ricercaData(list l, Data data);
int ricercaOrario(list l, int h,int m);
void scriviFileCorso(list l);

/*
static struct node* insertNode(struct node* l, int pos, Corso val);
static struct node* removeNode(struct node* l, int pos);
*/
#endif