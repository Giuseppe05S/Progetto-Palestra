//
// Created by Giuseppe on 28/04/2025.
//
#ifndef CORSO_H
#define CORSO_H

#include "utils.h"
#include "data.h"
#include <stdio.h>

typedef struct corso *Corso;
typedef struct orario *Orario;

/*
 * Funzione: creaCorso
 * -------------------
 * Crea un nuovo oggetto Corso con i parametri specificati.
 *
 * Parametri:
 *   ID: identificatore univoco del corso (stringa).
 *   nome: nome del corso (stringa).
 *   dataLezione: data della lezione (tipo Data).
 *   ora: ora di inizio della lezione (0-23).
 *   minuti: minuti di inizio della lezione (0-59).
 *   nPartecipanti: numero iniziale di partecipanti.
 *
 * Pre-condizione:
 *   ID e nome devono essere stringhe valide non nulle;
 *   dataLezione deve essere una data valida;
 *   ora deve essere compresa tra 0 e 23;
 *   minuti deve essere compreso tra 0 e 59;
 *   nPartecipanti deve essere >= 0.
 *
 * Post-condizione:
 *   Viene restituito un nuovo oggetto Corso allocato in memoria.
 *
 * Ritorna:
 *   Puntatore a un nuovo oggetto Corso.
 */
Corso creaCorso(string ID, string nome, Data dataLezione, int ora,int minuti,int nPartecipanti);
/*
 * Funzione: stampaCorso
 * ---------------------
 * Stampa tutte le informazioni di un corso su standard output.
 *
 * Parametri:
 *   co: puntatore al corso da stampare.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso.
 *
 * Post-condizione:
 *   Le informazioni del corso vengono stampate su stdout.
 *
 * Ritorna:
 *   Niente (void).
 */

void stampaCorso(Corso co);
/*
 * Funzione: Disponibilita
 * -----------------------
 * Restituisce la disponibilità di posti nel corso.
 *
 * Parametri:
 *   co: puntatore al corso.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso.
 *
 * Post-condizione:
 *   Viene restituito il numero di posti disponibili.
 *
 * Ritorna:
 *   Numero intero rappresentante i posti disponibili.
 */
int Disponibilita(Corso co);
/*
 * Funzione: getIDCorso
 * --------------------
 * Restituisce l'identificatore del corso.
 *
 * Parametri:
 *   co: puntatore al corso.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso.
 *
 * Post-condizione:
 *   Viene restituito l'ID del corso.
 *
 * Ritorna:
 *   Stringa contenente l'ID del corso.
 */
string getIDCorso(Corso co);
/*
 * Funzione: getNomeCorso
 * ----------------------
 * Restituisce il nome del corso.
 *
 * Parametri:
 *   co: puntatore al corso.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso.
 *
 * Post-condizione:
 *   Viene restituito il nome del corso.
 *
 * Ritorna:
 *   Stringa contenente il nome del corso.
 */
string getNomeCorso(Corso co);
/*
 * Funzione: getDataCorso
 * ----------------------
 * Restituisce la data della lezione del corso.
 *
 * Parametri:
 *   co: puntatore al corso.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso.
 *
 * Post-condizione:
 *   Viene restituita la data della lezione.
 *
 * Ritorna:
 *   Oggetto Data rappresentante la data della lezione.
 */
Data getDataCorso(Corso co);
/*
 * Funzione: getOrario
 * -------------------
 * Restituisce l'orario di inizio del corso.
 *
 * Parametri:
 *   co: puntatore al corso.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso.
 *
 * Post-condizione:
 *   Viene restituito l'orario di inizio del corso.
 *
 * Ritorna:
 *   Puntatore a un oggetto Orario.
 */
Orario getOrario(Corso co);
/*
 * Funzione: getNumPartecipantiCorso
 * ---------------------------------
 * Restituisce il numero di partecipanti al corso.
 *
 * Parametri:
 *   co: puntatore al corso.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso.
 *
 * Post-condizione:
 *   Viene restituito il numero di partecipanti.
 *
 * Ritorna:
 *   Numero intero dei partecipanti al corso.
 */
int getNumPartecipantiCorso(Corso co);
/*
 * Funzione: confrontaOrario
 * -------------------------
 * Confronta due orari e restituisce il risultato del confronto.
 *
 * Parametri:
 *   o1: primo orario da confrontare.
 *   o2: secondo orario da confrontare.
 *
 * Pre-condizione:
 *   o1 e o2 devono essere puntatori validi a oggetti Orario.
 *
 * Post-condizione:
 *   Viene restituito un valore che indica il risultato del confronto.
 *
 * Ritorna:
 *   Intero: < 0 se o1 < o2, 0 se o1 == o2, > 0 se o1 > o2.
 */
int confrontaOrario(Orario o1, Orario o2);
/*
 * Funzione: creaOrario
 * --------------------
 * Crea un nuovo oggetto Orario con ore e minuti specificati.
 *
 * Parametri:
 *   ora: valore dell'ora (0-23).
 *   minuti: valore dei minuti (0-59).
 *
 * Pre-condizione:
 *   ora deve essere compreso tra 0 e 23;
 *   minuti deve essere compreso tra 0 e 59.
 *
 * Post-condizione:
 *   Viene restituito un nuovo oggetto Orario allocato in memoria.
 *
 * Ritorna:
 *   Puntatore a un nuovo oggetto Orario.
 */
Orario creaOrario(int ora,int minuti);
/*
 * Funzione: scriviCorso
 * ---------------------
 * Scrive le informazioni del corso su un file.
 *
 * Parametri:
 *   co: puntatore al corso da scrivere.
 *   fp: puntatore al file di output.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso;
 *   fp deve essere un puntatore valido a un file aperto in scrittura.
 *
 * Post-condizione:
 *   Le informazioni del corso vengono scritte nel file.
 *
 * Ritorna:
 *   Niente (void).
 */
void scriviCorso(Corso co,FILE *fp);
/*
 * Funzione: incrementaPartecipanti
 * --------------------------------
 * Incrementa di uno il numero di partecipanti al corso.
 *
 * Parametri:
 *   co: puntatore al corso.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso.
 *
 * Post-condizione:
 *   Il numero di partecipanti viene incrementato di 1.
 *
 * Ritorna:
 *   Niente (void).
 */
void incrementaPartecipanti(Corso co);
/*
 * Funzione: stampaCorsoEssenziale
 * -------------------------------
 * Stampa solo le informazioni essenziali del corso.
 *
 * Parametri:
 *   co: puntatore al corso da stampare.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso.
 *
 * Post-condizione:
 *   Le informazioni essenziali del corso vengono stampate su stdout.
 *
 * Ritorna:
 *   Niente (void).
 */
void stampaCorsoCompatta(Corso co);
/*
 * Funzione: decrementaPartecipanti
 * --------------------------------
 * Decrementa di uno il numero di partecipanti al corso.
 *
 * Parametri:
 *   co: puntatore al corso.
 *
 * Pre-condizione:
 *   co deve essere un puntatore valido a un oggetto Corso;
 *   il numero di partecipanti deve essere > 0.
 *
 * Post-condizione:
 *   Il numero di partecipanti viene decrementato di 1.
 *
 * Ritorna:
 *   Niente (void).
 */
void decrementaPartecipanti(Corso co);
#endif