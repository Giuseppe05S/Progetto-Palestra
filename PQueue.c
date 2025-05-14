//FILE PQueue.c

#include"PQueue.h"
#include<stdio.h>
#include<stdlib.h>
#include "prenotazione.h"

#define MAXPQ 50

struct c_PQ
{
    Prenotazione vet[MAXPQ];
    int numel;
};

static void scendi (PQueue q);
static void sali (PQueue q);

PQueue newPQ()
{
    PQueue q = malloc(sizeof(struct c_PQ));
    if(q == NULL)
        return NULL;

    q->numel = 0;
    return q;
}

int emptyPQ(PQueue q)
{
    if(q->numel == 0)
    {
        return 1;
    }
    return 0;
}

int getMAX(PQueue q)
{
    if (q == NULL || q->numel == 0) // Se la coda è vuota o non inizializzata
        return -1; // valore di errore

    return q->vet[1]; // Restituisce la radice dell'heap (la chiave con priorità massima)
}

static void scendi (PQueue q)
{
    int temp, n = q->numel, i = 1, pos;
    while (1) //ciclo infinito
    {
        //n è il numero di elementi nell'array, quindi rappresenta l'ultimo indice valido dell'array
        /*verifica se il figlio destro del nodo è dentro i limiti dell'array (ossia se esiste). 
        Se questa condizione è vera, significa che il nodo corrente ha sia 
        un figlio sinistro (che è sempre presente se 2 * i <= n) che un figlio destro.*/
        if (2*i+1 <= n) // IL NODO CORRENTE HA 2 FIGLI
            // Confronta il figlio sinistro "[i*2]" e il figlio destro "[i * 2 + 1]"
            if (q->vet[i * 2] > q->vet[i * 2 + 1]) 
            {
                pos = i * 2;  // Se il figlio sinistro è maggiore, scegli il figlio sinistro
            } 
            else 
            {
                pos = i * 2 + 1;  // Altrimenti, scegli il figlio destro
            }
            
        else if (2*i <= n) // IL NODO CORRENTE HA 1 FIGLIO
            pos = 2*i;
        else break; // IL NODO CORRENTE NON HA FIGLI

        /* verifica se il valore presente nel nodo figlio (alla posizione pos) 
        è maggiore rispetto al valore del nodo corrente (alla posizione i).*/
        if (q->vet[pos] > q->vet[i]) //SCAMBIO LE CHIAVI E PROSEGUO
        {
            temp = q->vet[i];
            q->vet[i] = q->vet[pos];
            q->vet[pos] = temp;
            i = pos;
        }
        else
            break; // NON CI SONO PIU’ SCAMBI DA FARE, MI FERMO
    }
}

int deleteMax(PQueue q) //restituisce un valore 0 se l’operazione fallisce, 1 se termina con successo
{
    if (q == NULL || q->numel == 0) // Se la coda è vuota o non inizializzata
        return 0; // O un altro valore di errore appropriato
    
    q->vet[1] = q->vet[q->numel]; //SPOSTO L’ULTIMO ELEMENTO IN POSIZIONE 1
    q->numel --;

    scendi(q); // RIAGGIUSTO LO HEAP SCENDENDO
    return 1;
}

static void sali (PQueue q)
{
       // Variabile temporanea per lo scambio
       int temp;

       // pos: posizione del nuovo elemento inserito (ultima posizione)
       int pos = q->numel;
   
       // i: indice del padre del nodo in posizione pos
       int i = pos / 2;

    // Continua a salire finché non arriva alla radice (pos > 1)
    while (pos>1)
    {
        //Se l'elemento figlio è maggiore del padre, scambia
        if (q->vet[pos] > q->vet[i])
        {
            temp = q->vet[i];
            q->vet[i] = q->vet[pos];
            q->vet[pos] = temp;

            // Aggiorna la posizione: il nodo è salito di un livello
            pos = i;
            i = pos/2; // Calcola il nuovo padre
        }
    else
        break; // Se il padre è maggiore o uguale, l'heap è corretto → esci
    }
}

int insert (PQueue q, int key) //restituisce un valore 0 se l’operazione fallisce, 1 se termina con successo
{
    if (q == NULL || q->numel==MAXPQ) // CODA PIENA
        return 0; 
    
    q->numel++;
    q->vet[q->numel] = key; // INSERISCI IN ULTIMA POSIZIONE

    sali(q); // AGGIUSTA LO HEAP RISALENDO
    return 1;
}
