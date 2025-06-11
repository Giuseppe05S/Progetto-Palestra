//
// Created by Giuseppe on 28/04/2025.
//

#ifndef UTILS_H
#define UTILS_H

typedef char *string;

// Forward declarations
typedef struct hash* hashtable;
typedef struct c_list* list;
typedef struct c_listP *listP;
//posizione typedef string
/*
• Funzione: generaIDCliente
• ---------------------
• Genera un nuovo ID univoco per un cliente nel formato "CLT###".
*
• Post-condizione:
*  Un ID cliente valido viene creato.
*
• Ritorna:
*  Stringa allocata dinamicamente contenente l’ID del cliente.
*/
string generaIDCliente();
/*
• Funzione: generaIDPrenotazione
• ---------------------
• Genera un nuovo ID univoco per una prenotazione nel formato "PRT###".
*
• Post-condizione:
*  Un ID prenotazione valido viene creato.
*
• Ritorna:
*  Stringa allocata dinamicamente contenente l’ID della prenotazione.
*/
string generaIDPrenotazione();
/*
• Funzione: generaIDCorso
• ---------------------
• Genera un nuovo ID univoco per un corso nel formato "CRS###".
*
• Post-condizione:
*  Un ID corso valido viene creato.
*
• Ritorna:
*  Stringa allocata dinamicamente contenente l’ID del corso.
*/
string generaIDCorso();
/*
• Funzione: caricaFileClienti
• ---------------------
• Legge il file "iscritti.txt" e carica i clienti (iscritti) nella hashtable.
*
• Parametri:
*  h: hashtable dove inserire i clienti letti dal file.
*
• Pre-condizione:
*  Il file "iscritti.txt" deve esistere e avere formato corretto.
*
• Post-condizione:
*  Gli iscritti vengono caricati nella hashtable.
*/
void caricaFileClienti(hashtable h);
/*
• Funzione: caricaFileCorso
• ---------------------
• Legge il file "corsi.txt" e carica i corsi nella lista.
*
• Parametri:
*  l: lista in cui inserire i corsi letti dal file.
*
• Pre-condizione:
*  Il file "corsi.txt" deve esistere e avere formato corretto.
*
• Post-condizione:
*  I corsi vengono caricati nella lista.
*/
void caricaFileCorso(list l);
/*
• Funzione: caricaFilePrenotazioni
• ---------------------
• Legge il file "prenotazioni.txt" e carica le prenotazioni nella lista.
*
• Parametri:
*  l: lista in cui inserire le prenotazioni lette dal file.
*
• Pre-condizione:
*  Il file "prenotazioni.txt" deve esistere e avere formato corretto.
*
• Post-condizione:
*  Le prenotazioni vengono caricate nella lista.
*/
void caricaFilePrenotazioni(listP l);
/*
• Funzione: pulisciSchermo
• ---------------------
• Pulisce il terminale in modo compatibile con Windows e Unix.
*
• Post-condizione:
*  Il terminale viene ripulito.
*/
void pulisciSchermo();

#endif