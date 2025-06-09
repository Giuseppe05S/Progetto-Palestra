#ifndef LISTA_PRENOTAZIONE_H
#define LISTA_PRENOTAZIONE_H

#include "listaPrenotazione.h"
#include "data.h"

// Forward declaration
typedef struct prenotazione *Prenotazione;
typedef struct c_listP *listP;
typedef char *string;

/*
•  Funzione: newListPrenotati
•  -------------------------
•  Crea una nuova lista vuota di prenotazioni.
*
•  Parametri:
*   Nessun parametro.
*
•  Pre-condizione:
*   Nessuna.
*
•  Post-condizione:
*   Viene restituita una nuova lista vuota di prenotazioni allocata in memoria.
*
•  Ritorna:
*   Puntatore a una nuova lista di prenotazioni.
*/
listP newListPrenotati(void); //Crea una nuova lista vuota e restituisce la lista creata;
/*
•  Funzione: insertListPrenotati
•  ------------------------------
•  Inserisce una prenotazione in una posizione specifica della lista.
*
•  Parametri:
*   l: lista di prenotazioni dove inserire.
*   pos: posizione dove inserire (0 = testa della lista).
*   val: prenotazione da inserire.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   pos deve essere >= 0 e <= dimensione della lista.
*   val deve essere una prenotazione valida.
*
•  Post-condizione:
*   Viene restituito 1 se l'inserimento è avvenuto con successo, 0 altrimenti.
*
•  Ritorna:
*   1 se l'inserimento è riuscito, 0 altrimenti.
*/
int insertListPrenotati(listP l, int pos, Prenotazione val);
/*
•  Funzione: removeListPrenotati
•  ------------------------------
•  Rimuove una prenotazione dalla posizione specificata nella lista.
*
•  Parametri:
*   l: lista di prenotazioni da cui rimuovere.
*   pos: posizione dell'elemento da rimuovere (0 = primo elemento).
*
•  Pre-condizione:
*   l deve essere una lista valida e non vuota.
*   pos deve essere >= 0 e < dimensione della lista.
*
•  Post-condizione:
*   Viene restituito 1 se la rimozione è avvenuta con successo, 0 altrimenti.
*
•  Ritorna:
*   1 se la rimozione è riuscita, 0 altrimenti.
*/
int removeListPrenotati(listP l, int pos);
/*
•  Funzione: reverseListPrenotazioni
•  ----------------------------------
•  Crea una nuova lista con le prenotazioni in ordine inverso.
*
•  Parametri:
*   l: lista di prenotazioni da invertire.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*
•  Post-condizione:
*   Viene restituita una nuova lista con gli elementi in ordine inverso.
*
•  Ritorna:
*   Puntatore alla nuova lista invertita.
*/
listP reverseListPrenotazioni(listP l);
/*
•  Funzione: ricercaListaPrenotati
•  --------------------------------
•  Cerca prenotazioni nella lista in base a criteri specificati.
*
•  Parametri:
*   l: lista di prenotazioni in cui cercare.
*   sel: criterio di ricerca (0=ID Cliente, 1=ID Corso, 2=ID Prenotazione).
*   str: stringa da cercare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   sel deve essere 0, 1 o 2.
*   str deve essere una stringa valida.
*
•  Post-condizione:
*   Viene restituita una nuova lista contenente solo le prenotazioni che corrispondono al criterio.
*
•  Ritorna:
*   Puntatore alla lista contenente i risultati della ricerca.
*/
listP ricercaListaPrenotati(listP l, int sel,string str);//0 per Cliente e 1 per Corso
/*
•  Funzione: stampaListaPrenotazioni
•  ----------------------------------
•  Stampa tutte le prenotazioni presenti nella lista.
*
•  Parametri:
*   l: lista di prenotazioni da stampare.
*
•  Pre-condizione:
*   l può essere una lista valida o NULL.
*
•  Post-condizione:
*   Tutte le prenotazioni vengono stampate a video.
*
•  Ritorna:
*   Nessun valore di ritorno (void).
*/
void stampaListaPrenotazioni(listP l);
/*
•  Funzione: isEmptyPrenotazione
•  ------------------------------
•  Verifica se la lista di prenotazioni è vuota.
*
•  Parametri:
*   l: lista di prenotazioni da verificare.
*
•  Pre-condizione:
*   Nessuna (gestisce anche liste NULL).
*
•  Post-condizione:
*   Viene restituito 1 se la lista è vuota, 0 altrimenti.
*
•  Ritorna:
*   1 se la lista è vuota o NULL, 0 altrimenti.
*/
int isEmptyPrenotazione(listP l);
/*
•  Funzione: ricercaDataPrenotazione
•  ----------------------------------
•  Cerca e stampa tutte le prenotazioni effettuate in un mese specifico.
*
•  Parametri:
*   l: lista di prenotazioni in cui cercare.
*   mm: mese da cercare (1-12).
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   mm deve essere compreso tra 1 e 12.
*
•  Post-condizione:
*   Viene restituito 1 se è stata trovata almeno una prenotazione, 0 altrimenti.
*
•  Ritorna:
*   1 se è stata trovata almeno una prenotazione del mese specificato, 0 altrimenti.
*/
int ricercaDataPrenotazione(listP l, int mm);
/*
•  Funzione: scriviFilePrenotazione
•  ---------------------------------
•  Salva tutte le prenotazioni della lista in un file di testo.
*
•  Parametri:
*   l: lista di prenotazioni da salvare.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   Deve essere possibile creare/scrivere il file "prenotazioni.txt".
*
•  Post-condizione:
*   Tutte le prenotazioni vengono scritte nel file "prenotazioni.txt".
*
•  Ritorna:
*   Nessun valore di ritorno (void).
*/
void scriviFilePrenotazione(listP l);
/*
•  Funzione: cancellaPrenotazioneDi
•  ---------------------------------
•  Cancella tutte le prenotazioni associate a un cliente o a un corso specifico.
*
•  Parametri:
*   l: lista di prenotazioni da cui cancellare.
*   sel: criterio di cancellazione (0=cliente, 1=corso).
*   ID: ID del cliente o del corso.
*
•  Pre-condizione:
*   l deve essere una lista valida e non vuota.
*   sel deve essere 0 o 1.
*   ID deve essere una stringa valida.
*
•  Post-condizione:
*   Viene restituito il numero di prenotazioni cancellate.
*
•  Ritorna:
*   Numero di prenotazioni cancellate.
*/
int cancellaPrenotazioneDi(listP l,int sel,string ID);//0 per Cliente e 1 per Corso
/*
•  Funzione: cancellaPrenotazione
•  -------------------------------
•  Cancella una specifica prenotazione identificata da ID prenotazione e ID cliente.
*
•  Parametri:
*   l: lista di prenotazioni da cui cancellare.
*   IDCorso: ID della prenotazione da cancellare.
*   IDCliente: ID del cliente che ha effettuato la prenotazione.
*
•  Pre-condizione:
*   l deve essere una lista valida.
*   IDCorso e IDCliente devono essere stringhe valide.
*
•  Post-condizione:
*   Viene restituito 1 se la prenotazione è stata trovata e cancellata, 0 altrimenti.
*
•  Ritorna:
*   1 se la prenotazione è stata cancellata con successo, 0 altrimenti.
*/
int cancellaPrenotazione(listP l,string IDCorso,string IDCliente);
/*
•  Funzione: getFirstPrenotazione
•  -------------------------------
•  Restituisce la prima prenotazione della lista senza rimuoverla.
*
•  Parametri:
*   l: lista di prenotazioni da cui ottenere il primo elemento.
*
•  Pre-condizione:
*   l deve essere una lista valida e non vuota.
*
•  Post-condizione:
*   Viene restituita la prima prenotazione della lista.
*
•  Ritorna:
*   La prima prenotazione della lista.
*/
Prenotazione getFirstPrenotazione(listP l);
#endif