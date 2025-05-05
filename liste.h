//file liste.h

#include "iscritto.h"

typedef struct c_list *list;


list newList(void); //Crea una nuova lista vuota e restituisce la lista creata;
int insertList(list l, int pos, Iscritto val);

static struct node* insertNode(struct node* l, int pos, Iscritto val);

int removeList(list l, int pos);

static struct node* removeNode(struct node* l, int pos);