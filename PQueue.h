//FILE PQueue.h

//VERSIONE SEMPLIFICATA CON SOLO CHIAVE DI TIPO INTERO, SENZA VALORI ASSOCIATI

typedef struct c_PQ *PQueue;

PQueue newPQ(void);
int emptyPQ(PQueue q);
int getMax(PQueue q);
int deleteMax(PQueue q);
int insert (PQueue q, int key);

/*Gli operatori insert() e
deleteMax() restituiscono un
valore 0 se l’operazione fallisce, 1
se termina con successo*/
