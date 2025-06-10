//
// Created by Giuseppe on 28/04/2025.
//
#ifndef ISCRITTO_H
#define ISCRITTO_H

#include "utils.h"
#include "data.h"
#include <stdio.h>

typedef struct iscritto *Iscritto;
/*
•  Funzione: CreaIscritto
•  ---------------------
•  Crea un nuovo oggetto Iscritto con i dati specificati.
*
•  Parametri:
*   nome: nome dell'iscritto.
*   cognome: cognome dell'iscritto.
*   dataIscrizione: data di iscrizione dell'iscritto.
*   durata: durata dell'abbonamento in mesi.
*   ID: identificativo univoco dell'iscritto.
*
•  Pre-condizione:
*   nome e cognome devono essere stringhe valide non vuote;
*   dataIscrizione deve essere una data valida;
*   durata deve essere un valore positivo maggiore di 0;
*   ID deve essere una stringa valida di massimo 6 caratteri.
*
•  Post-condizione:
*   Viene restituito un nuovo oggetto Iscritto allocato in memoria.
*   La data di scadenza viene calcolata automaticamente.
*
•  Ritorna:
*   Puntatore a un nuovo oggetto Iscritto.
*/
Iscritto CreaIscritto(string nome, string cognome, Data dataIscrizione, int durata,string ID);
/*
•  Funzione: getNext
•  ---------------------
•  Restituisce il puntatore al prossimo iscritto nella lista collegata.
*
•  Parametri:
*   is: iscritto di cui ottenere il successore.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Viene restituito il puntatore al prossimo iscritto.
*
•  Ritorna:
*   Puntatore al prossimo iscritto o NULL se non esiste.
*/
Iscritto getNext(Iscritto is);
/*
•  Funzione: stampaCliente
•  ---------------------
•  Stampa tutte le informazioni dettagliate di un iscritto.
*
•  Parametri:
*   is: iscritto di cui stampare le informazioni.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Le informazioni dell'iscritto vengono stampate su stdout.
*
•  Ritorna:
*   Nessun valore (void).
*/

void stampaCliente(Iscritto is);
/*
•  Funzione: stampaMinimaCliente
•  ---------------------
•  Stampa le informazioni essenziali di un iscritto in formato tabellare.
*
•  Parametri:
*   is: iscritto di cui stampare le informazioni essenziali.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   ID, cognome e nome vengono stampati in formato allineato.
*
•  Ritorna:
*   Nessun valore (void).
*/
void stampaMinimaCliente(Iscritto is);
/*
•  Funzione: getID
•  ---------------------
•  Restituisce l'identificativo univoco dell'iscritto.
*
•  Parametri:
*   is: iscritto di cui ottenere l'ID.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Viene restituito l'ID dell'iscritto.
*
•  Ritorna:
*   Stringa contenente l'ID dell'iscritto.
*/
string getID(Iscritto is);
/*
•  Funzione: getNome
•  ---------------------
•  Restituisce il nome dell'iscritto.
*
•  Parametri:
*   is: iscritto di cui ottenere il nome.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Viene restituito il nome dell'iscritto.
*
•  Ritorna:
*   Stringa contenente il nome dell'iscritto.
*/

string getNome(Iscritto is);
/*
•  Funzione: getCognome
•  ---------------------
•  Restituisce il cognome dell'iscritto.
*
•  Parametri:
*   is: iscritto di cui ottenere il cognome.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Viene restituito il cognome dell'iscritto.
*
•  Ritorna:
*   Stringa contenente il cognome dell'iscritto.
*/
string getCognome(Iscritto is);
/*
•  Funzione: getDurata
•  ---------------------
•  Restituisce la durata dell'abbonamento dell'iscritto.
*
•  Parametri:
*   is: iscritto di cui ottenere la durata abbonamento.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Viene restituita la durata dell'abbonamento in mesi.
*
•  Ritorna:
*   Intero rappresentante la durata in mesi.
*/
int getDurata(Iscritto is);
/*
•  Funzione: setNext
•  ---------------------
•  Imposta il puntatore al prossimo iscritto nella lista collegata.
*
•  Parametri:
*   is: iscritto a cui impostare il successore.
*   next: puntatore al prossimo iscritto.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto;
*   next può essere un puntatore valido o NULL.
*
•  Post-condizione:
*   Il campo next dell'iscritto viene aggiornato.
*
•  Ritorna:
*   Nessun valore (void).
*/
Data getDataScadenza(Iscritto is);
void setNext(Iscritto is, Iscritto next);
/*
•  Funzione: rinnovaAbbonamento
•  ---------------------
•  Rinnova l'abbonamento di un iscritto estendendo la durata.
*
•  Parametri:
*   is: iscritto a cui rinnovare l'abbonamento.
*   durata: mesi aggiuntivi di abbonamento.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto;
*   durata deve essere un valore positivo maggiore di 0.
*
•  Post-condizione:
*   La durata totale e la data di scadenza vengono aggiornate.
*
•  Ritorna:
*   Nessun valore (void).
*/
void rinnovaAbbonamento(Iscritto is, int durata);
/*
•  Funzione: eliminaIscritto
•  ---------------------
•  Elimina completamente un iscritto liberando la memoria allocata.
*
•  Parametri:
*   is: iscritto da eliminare.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Tutta la memoria allocata per l'iscritto viene liberata.
*
•  Ritorna:
*   Nessun valore (void).
*/
void eliminaIscritto(Iscritto is);
/*
•  Funzione: controlloAbbonamento
•  ---------------------
•  Verifica se l'abbonamento di un iscritto è ancora valido.
*
•  Parametri:
*   is: iscritto di cui controllare l'abbonamento.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Viene restituito lo stato dell'abbonamento.
*
•  Ritorna:
*   0 se l'abbonamento è valido, 1 se scaduto, -1 se dati non validi.
*/
int controlloAbbonamento(Iscritto is);
/*
•  Funzione: scriviCliente
•  ---------------------
•  Scrive le informazioni di un iscritto su file in formato strutturato.
*
•  Parametri:
*   is: iscritto di cui scrivere le informazioni.
*   fp: puntatore al file aperto in modalità scrittura.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto;
*   fp deve essere un file aperto e valido per la scrittura.
*
•  Post-condizione:
*   I dati dell'iscritto vengono scritti nel file.
*
•  Ritorna:
*   Nessun valore (void).
*/
void scriviCliente(Iscritto is,FILE *fp);
#endif