//
// Created by Giuseppe on 28/04/2025.
//
#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#include "data.h"
#include "utils.h"
#include <stdio.h>

typedef struct prenotazione *Prenotazione;

/*
•  Funzione: creaPrenotazione
•  -----------------------------------
•  Crea una nuova prenotazione nel sistema.
*
•  Parametri:
*   IDPrenotazione: identificativo univoco della prenotazione.
*   IDCorso: identificativo del corso da prenotare.
*   IDCliente: identificativo del cliente che effettua la prenotazione.
*   dataPrenotazione: data in cui viene effettuata la prenotazione.
*
•  Pre-condizione:
*   Tutti i parametri devono essere non NULL.
*   dataPrenotazione deve essere una data valida.
*
•  Ritorna:
*   Puntatore alla nuova prenotazione se successo, NULL se errore.
*/
Prenotazione creaPrenotazione(string IDPrenotazione, string IDCorso, string IDCliente, Data dataPrenotazione);

/*
•  Funzione: eliminaPrenotazione
•  -----------------------------------
•  Elimina una prenotazione liberando tutta la memoria associata.
*
•  Parametri:
*   pr: prenotazione da eliminare.
*
•  Pre-condizione:
*   pr può essere NULL (gestito dalla funzione).
*
•  Ritorna:
*   Nulla (void).
*/
void eliminaPrenotazione(Prenotazione pr);
/*
•  Funzione: getDataPrenotazione
•  -----------------------------------
•  Restituisce la data della prenotazione specificata.
*
•  Parametri:
*   pr: prenotazione da cui estrarre la data.
*
•  Pre-condizione:
*   pr deve essere una prenotazione valida (non NULL).
*
•  Ritorna:
*   Data associata alla prenotazione.
*/
Data getDataPrenotazione(Prenotazione pr);
/*
•  Funzione: getIDClientePrenotazione
•  -----------------------------------
•  Restituisce l'identificativo del cliente associato alla prenotazione.
*
•  Parametri:
*   pr: prenotazione da cui estrarre l'ID cliente.
*
•  Pre-condizione:
*   pr deve essere una prenotazione valida (non NULL).
*
•  Ritorna:
*   String contenente l'ID del cliente.
*/
string getIDClientePrenotazione(Prenotazione pr);
/*
•  Funzione: getIDCorsoPrenotazione
•  -----------------------------------
•  Restituisce l'identificativo del corso associato alla prenotazione.
*
•  Parametri:
*   pr: prenotazione da cui estrarre l'ID corso.
*
•  Pre-condizione:
*   pr deve essere una prenotazione valida (non NULL).
*
•  Ritorna:
*   String contenente l'ID del corso.
*/
string getIDCorsoPrenotazione(Prenotazione pr);
/*
•  Funzione: getIDPrenotazione
•  -----------------------------------
•  Restituisce l'identificativo univoco della prenotazione.
*
•  Parametri:
*   pr: prenotazione da cui estrarre l'ID.
*
•  Pre-condizione:
*   pr deve essere una prenotazione valida (non NULL).
*
•  Ritorna:
*   String contenente l'ID univoco della prenotazione.
*/
string getIDPrenotazione(Prenotazione pr);

/*
•  Funzione: stampaPrenotazione
•  -----------------------------------
•  Stampa su console tutti i dettagli della prenotazione in formato leggibile.
*
•  Parametri:
*   p: prenotazione da stampare.
*
•  Pre-condizione:
*   p può essere NULL (gestito dalla funzione).
*
•  Ritorna:
*   Nulla (void).
*/
void stampaPrenotazione(Prenotazione p);
/*
•  Funzione: scriviPrenotazione
•  -----------------------------------
•  Scrive i dati della prenotazione su file in formato strutturato.
*
•  Parametri:
*   p: prenotazione da scrivere su file.
*   fp: puntatore al file di output aperto in scrittura.
*
•  Pre-condizione:
*   p deve essere una prenotazione valida.
*   fp deve essere un file aperto in modalità scrittura.
*
•  Ritorna:
*   Nulla (void).
*/
void scriviPrenotazione(Prenotazione p,FILE *fp);
#endif