//file liste.h
#ifndef LISTE_H
#define LISTE_H

#include "corso.h"

// Forward declaration
typedef struct corso *Corso;
typedef struct c_list *list;

/*
•  Funzione: newList
•  -----------------------------------
•  Crea una nuova lista vuota e restituisce la lista creata.
*
•  Parametri:
*   Nessuno.
*
•  Pre-condizione:
*   Nessuna.
*
•  Post-condizione:
*   Viene creata una nuova lista vuota.
*   Restituisce il puntatore alla lista creata o NULL se l'allocazione fallisce.
*
•  Ritorna:
•  - Puntatore alla nuova lista creata.
•  - NULL se l'allocazione della memoria fallisce.
*/
list newList(void);
/*
•  Funzione: insertList
•  -----------------------------------
•  Inserisce un corso in una posizione specifica della lista.
*
•  Parametri:
*   l: lista in cui inserire.
*   pos: posizione di inserimento (0 = inizio).
*   val: corso da inserire.
*
•  Pre-condizione:
*   l deve essere una lista valida (non NULL).
*   pos deve essere >= 0 e <= dimensione lista.
*   val deve essere un corso valido.
*
•  Post-condizione:
*   Il corso viene inserito nella posizione specificata.
*   La dimensione della lista viene incrementata di 1.
*   Restituisce 1 se successo, 0 se errore.
*
•  Ritorna:
•  - 1 se l'inserimento è avvenuto con successo.
•  - 0 se si è verificato un errore (es. allocazione memoria, posizione non valida).
*/
int insertList(list l, int pos, Corso val);
/*
•  Funzione: removeList
•  -----------------------------------
•  Rimuove un corso da una posizione specifica della lista.
*
•  Parametri:
*   l: lista da cui rimuovere.
*   pos: posizione del corso da rimuovere.
*
•  Pre-condizione:
*   l deve essere una lista valida e non vuota.
*   pos deve essere >= 0 e < dimensione lista.
*
•  Post-condizione:
*   Il corso viene rimosso dalla posizione specificata.
*   La dimensione della lista viene decrementata di 1.
*   Restituisce 1 se successo, 0 se errore.
*
•  Ritorna:
•  - 1 se la rimozione è avvenuta con successo.
•  - 0 se si è verificato un errore (es. lista vuota, posizione non valida).
*/
int removeList(list l, int pos);
/*
•  Funzione: stampaLista
•  -----------------------------------
•  Stampa tutti i corsi presenti nella lista in formato completo.
*
•  Parametri:
*   l: lista da stampare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*
•  Post-condizione:
*   Tutti i corsi vengono stampati a video.
*   Se la lista è vuota, viene stampato un messaggio appropriato.
*
•  Ritorna:
•  - Nessun valore di ritorno (void).
•  - Stampa a video tutti i corsi o un messaggio se la lista è vuota.
*/
void stampaLista(list l);
/*
•  Funzione: reverseList
•  -----------------------------------
•  Crea una nuova lista con i corsi in ordine inverso.
*
•  Parametri:
*   l: lista da invertire.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*
•  Post-condizione:
*   Viene creata una nuova lista con gli elementi in ordine inverso.
*   La lista originale rimane invariata.
*   Restituisce la nuova lista invertita.
*
•  Ritorna:
•  - Puntatore alla nuova lista invertita.
•  - La lista originale rimane invariata.
*/
list reverseList(list l);
/*
•  Funzione: ricercaGenericaLista
•  -----------------------------------
•  Cerca corsi nella lista in base a ID o nome.
*
•  Parametri:
*   l: lista in cui cercare.
*   sel: criterio di ricerca (0=ID, 1=Nome).
*   str: stringa da cercare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   sel deve essere 0 o 1.
*   str deve essere una stringa valida.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente i corsi che corrispondono al criterio.
*   La lista originale rimane invariata.
*   Restituisce la lista dei risultati.
*
•  Ritorna:
•  - Puntatore alla nuova lista contenente i corsi che corrispondono al criterio.
•  - Lista vuota se nessun corso corrisponde al criterio.
*/
list ricercaGenericaLista(list l, int sel,string str);
/*
•  Funzione: isEmpty
•  -----------------------------------
•  Verifica se una lista è vuota.
*
•  Parametri:
*   l: lista da verificare.
*
•  Pre-condizione:
*   Nessuna (gestisce anche liste NULL).
*
•  Post-condizione:
*   Restituisce 1 se la lista è vuota o NULL, 0 altrimenti.
*
•  Ritorna:
•  - 1 se la lista è vuota o NULL.
•  - 0 se la lista contiene almeno un elemento.
*/
int isEmpty(list l);
/*
•  Funzione: ricercaData
•  -----------------------------------
•  Cerca corsi che si svolgono in una data specifica.
*
•  Parametri:
*   l: lista in cui cercare.
*   data: data da cercare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   data deve essere una data valida.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente i corsi della data specificata.
*   La lista originale rimane invariata.
*   Restituisce la lista dei risultati.
*
•  Ritorna:
•  - Puntatore alla nuova lista contenente i corsi della data specificata.
•  - Lista vuota se nessun corso corrisponde alla data.
*/
list ricercaData(list l, Data data);
/*
•  Funzione: ricercaOrario
•  -----------------------------------
•  Cerca corsi che si svolgono a un orario specifico.
*
•  Parametri:
*   l: lista in cui cercare.
*   h: ora da cercare.
*   m: minuti da cercare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   h deve essere tra 0 e 23.
*   m deve essere tra 0 e 59.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente i corsi dell'orario specificato.
*   La lista originale rimane invariata.
*   Restituisce la lista dei risultati.
*
•  Ritorna:
•  - Puntatore alla nuova lista contenente i corsi dell'orario specificato.
•  - Lista vuota se nessun corso corrisponde all'orario.
*/
list ricercaOrario(list l, int h,int m);
/*
•  Funzione: lezioniInEvidenza
•  -----------------------------------
•  Trova i tre corsi con il maggior numero di partecipanti.
*
•  Parametri:
*   l: lista in cui cercare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente i primi tre corsi per numero di partecipanti.
*   La lista è ordinata dal primo al terzo posto.
*   Restituisce la lista dei corsi in evidenza.
*
•  Ritorna:
•  - Puntatore alla nuova lista contenente i primi tre corsi per numero di partecipanti.
•  - Lista ordinata dal primo al terzo posto.
•  - NULL se la lista originale è vuota.
*/
list lezioniInEvidenza(list l);
/*
•  Funzione: scriviFileCorso
•  -----------------------------------
•  Salva tutti i corsi della lista nel file "corsi.txt".
*
•  Parametri:
*   l: lista da salvare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   Deve essere possibile creare/scrivere il file "corsi.txt".
*
•  Post-condizione:
*   Tutti i corsi vengono salvati nel file.
*   Il file viene chiuso correttamente.
*
•  Ritorna:
•  - Nessun valore di ritorno (void).
•  - Salva tutti i corsi nel file "corsi.txt".
*/
void scriviFileCorso(list l);
/*
•  Funzione: getFirstCorso
•  -----------------------------------
•  Restituisce il primo corso della lista.
*
•  Parametri:
*   l: lista da cui estrarre il primo corso.
*
•  Pre-condizione:
*   l deve essere una lista valida e non vuota.
*
•  Post-condizione:
*   Restituisce il primo corso della lista o NULL se la lista è vuota.
*   La lista rimane invariata.
*
•  Ritorna:
•  - Puntatore al primo corso della lista.
•  - NULL se la lista è vuota o non inizializzata.
*/
Corso getFirstCorso(list l);
/*
•  Funzione: ricercaMese
•  -----------------------------------
•  Cerca corsi che si svolgono in un mese specifico.
*
•  Parametri:
*   l: lista in cui cercare.
*   mm: mese da cercare (1-12).
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   mm deve essere un valore tra 1 e 12.
*
•  Post-condizione:
*   Viene creata una nuova lista contenente i corsi del mese specificato.
*   La lista originale rimane invariata.
*   Restituisce la lista dei risultati.
*
•  Ritorna:
•  - Puntatore alla nuova lista contenente i corsi del mese specificato.
•  - Lista vuota se nessun corso si svolge nel mese indicato.
*/
list ricercaMese(list l, int mm);
/*
•  Funzione: cancellaCorso
•  -----------------------------------
•  Cerca e rimuove un corso dalla lista usando il suo ID.
*
•  Parametri:
*   l: lista da cui rimuovere il corso.
*   IDCorso: ID del corso da rimuovere.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   IDCorso deve essere una stringa valida.
*
•  Post-condizione:
*   Il corso con l'ID specificato viene rimosso se trovato.
*   Restituisce 1 se il corso è stato rimosso, 0 altrimenti.
*
•  Ritorna:
•  - 1 se il corso è stato trovato e rimosso con successo.
•  - 0 se il corso non è stato trovato o si è verificato un errore.
*/
int cancellaCorso(list l,string IDCorso);
/*
•  Funzione: stampaListaEssenziale
•  -----------------------------------
•  Stampa i corsi in formato tabellare compatto con solo le informazioni essenziali.
*
•  Parametri:
*   l: lista da stampare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*
•  Post-condizione:
*   I corsi vengono stampati in formato tabellare con ID, Nome, Data e Orario.
*   Se la lista è vuota, viene stampato un messaggio appropriato.
*
•  Ritorna:
•  - Nessun valore di ritorno (void).
•  - Stampa a video i corsi in formato tabellare compatto.
*/
void stampaListaEssenziale(list l);
/*
•  Funzione: scriviLezioniInEvidenza
•  -----------------------------------
•  Scrive i corsi in evidenza in un file con formato specifico.
*
•  Parametri:
*   l: lista dei corsi in evidenza da scrivere.
*   fp: puntatore al file aperto in scrittura.
*
•  Pre-condizione:
*   fp deve essere un file aperto in modalità scrittura.
*   l può essere NULL o vuota.
*
•  Post-condizione:
*   I corsi vengono scritti nel file con formato: ID Nome Data NumPartecipanti.
*   Se la lista è vuota, scrive un messaggio appropriato.
*
•  Ritorna:
•  - Nessun valore di ritorno (void).
•  - Scrive i corsi nel file con formato: ID Nome Data NumPartecipanti.
*/
void scriviLezioniInEvidenza(list l, FILE *fp);

/*
static struct node* insertNode(struct node* l, int pos, Corso val);
static struct node* removeNode(struct node* l, int pos);
*/
#endif