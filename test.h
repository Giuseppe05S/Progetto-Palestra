//
// Created by Giuseppe on 27/05/2025.
//

#ifndef TEST_H
#define TEST_H

typedef struct hash* hashtable;
typedef struct c_listP *listP;
typedef struct c_list *list;

typedef char *string;
/*
•  Funzione: mainTest
•  ---------------------
•  Funzione principale per eseguire una suite di test automatici.
*
•  Parametri:
*   hClienti: hashtable contenente tutti i clienti registrati nel sistema.
*   lCorsi: lista contenente tutti i corsi disponibili.
*   lPrenotazioni: lista contenente tutte le prenotazioni effettuate.
*
•  Pre-condizione:
*   Le strutture dati devono essere inizializzate correttamente;
*   Il file "testSuite.txt" deve esistere e contenere i test da eseguire.
*
•  Post-condizione:
*   Viene creato il file "testResult.txt" con i risultati di tutti i test.
*
•  Ritorna:
*   void (non restituisce valori).
*/
void mainTest(hashtable hClienti,list lCorsi, listP lPrenotazioni);
//int testCorrettaRegistrazionePrenotazione(string input,string output,string oracle, hashtable hClienti,list lCorsi);
/*
•  Funzione: confrontaFile
•  ---------------------
•  Confronta il contenuto di due file per verificare se sono identici.
*
•  Parametri:
*   file1: percorso del primo file da confrontare.
*   file2: percorso del secondo file da confrontare.
*
•  Pre-condizione:
*   Entrambi i file devono esistere e essere accessibili in lettura;
*   I percorsi dei file devono essere validi.
*
•  Post-condizione:
*   I file vengono letti e confrontati senza essere modificati.
*
•  Ritorna:
*   1 se i file hanno contenuto identico, 0 se sono diversi o si verifica un errore.
*/
int confrontaFile(string file1,string file2);


#endif //TEST_H
