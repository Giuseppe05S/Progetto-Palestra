//
// Created by Giuseppe on 28/04/2025.
//
#ifndef DATA_H
#define DATA_H
typedef struct data* Data;

/*
•  Funzione: creaData
•  ------------------
•  Crea un nuovo oggetto Data con giorno, mese e anno specificati.
*
•  Parametri:
*   giorno: valore del giorno (1–31).
*   mese: valore del mese (1–12).
*   anno: valore dell'anno.
*
•  Pre-condizione:
*   giorno deve essere compreso tra 1 e 31;
*   mese deve essere compreso tra 1 e 12.
*
•  Post-condizione:
*   Viene restituito un nuovo oggetto Data allocato in memoria.
*   Se la data non è valida, viene richiesto un nuovo inserimento.
*
•  Ritorna:
*   Puntatore a un nuovo oggetto Data.
*/
Data creaData(int giorno,int mese,int anno);
/*
•  Funzione: calcoloDataScadenza
•  -----------------------------
•  Calcola la data di scadenza aggiungendo una durata in mesi alla data fornita.
*
•  Parametri:
*   data: data di partenza per il calcolo.
*   durata: numero di mesi da aggiungere alla data.
*
•  Pre-condizione:
*   data deve essere valida (non NULL);
*   durata deve essere maggiore di 0.
*
•  Post-condizione:
*   Viene restituita una nuova data con la scadenza calcolata.
*   Gestisce automaticamente il passaggio all'anno successivo se necessario.
*
•  Ritorna:
*   Puntatore a un nuovo oggetto Data con la scadenza, NULL se errore.
*/
Data calcoloDataScadenza(Data data,int durata);
/*
•  Funzione: copiaData
•  -------------------
•  Crea una copia identica dell'oggetto Data fornito.
*
•  Parametri:
*   dataOriginale: data da copiare.
*
•  Pre-condizione:
*   dataOriginale deve essere valida (non NULL).
*
•  Post-condizione:
*   Viene restituita una nuova data identica all'originale.
*
•  Ritorna:
*   Puntatore a un nuovo oggetto Data copia, NULL se errore.
*/
Data copiaData(Data dataOriginale);
/*
•  Funzione: stampaData
•  --------------------
•  Stampa la data nel formato GG/MM/AAAA.
*
•  Parametri:
*   data: data da stampare.
*
•  Pre-condizione:
*   data deve essere valida (non NULL).
*
•  Post-condizione:
*   La data viene stampata su stdout nel formato specificato.
*/
void stampaData(Data data);
/*
•  Funzione: getGiorno
•  -------------------
•  Restituisce il giorno della data specificata.
*
•  Parametri:
*   data: data da cui estrarre il giorno.
*
•  Pre-condizione:
*   data deve essere valida (non NULL).
*
•  Post-condizione:
*   Viene restituito il valore del giorno.
*
•  Ritorna:
*   Valore del giorno (1-31), -1 se errore.
*/
int getGiorno(Data data);
/*
•  Funzione: getMese
•  -----------------
•  Restituisce il mese della data specificata.
*
•  Parametri:
*   data: data da cui estrarre il mese.
*
•  Pre-condizione:
*   data deve essere valida (non NULL).
*
•  Post-condizione:
*   Viene restituito il valore del mese.
*
•  Ritorna:
*   Valore del mese (1-12), -1 se errore.
*/
int getMese(Data data);
/*
•  Funzione: getAnno
•  -----------------
•  Restituisce l'anno della data specificata.
*
•  Parametri:
*   data: data da cui estrarre l'anno.
*
•  Pre-condizione:
*   data deve essere valida (non NULL).
*
•  Post-condizione:
*   Viene restituito il valore dell'anno.
*
•  Ritorna:
*   Valore dell'anno, -1 se errore.
*/
int getAnno(Data data);
/*
•  Funzione: confrontaData
•  -----------------------
•  Confronta due date e restituisce il risultato del confronto.
*
•  Parametri:
*   d1: prima data da confrontare.
*   d2: seconda data da confrontare.
*
•  Pre-condizione:
*   Entrambe le date devono essere valide (non NULL).
*
•  Post-condizione:
*   Viene restituito il risultato del confronto cronologico.
*
•  Ritorna:
*   -1 se d1 < d2, 0 se d1 == d2, 1 se d1 > d2.
*/
int confrontaData(Data d1, Data d2);
/*
•  Funzione: dataOggi
•  ------------------
•  Crea un oggetto Data con la data corrente del sistema.
*
•  Parametri:
*   Nessuno.
*
•  Pre-condizione:
*   Nessuna.
*
•  Post-condizione:
*   Viene restituita la data corrente del sistema.
*
•  Ritorna:
*   Puntatore a un nuovo oggetto Data con la data corrente.
*/
Data dataOggi();
#endif
