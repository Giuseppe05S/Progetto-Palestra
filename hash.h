//
// Created by Giuseppe on 09/05/2025.
//
#ifndef HASH_H
#define HASH_H
#include "iscritto.h"
#include "utils.h"
//aggiunti secondo l'ai
typedef struct iscritto* Iscritto;
typedef char* string;
//.
typedef struct hash* hashtable;

/*
 * Funzione: newHashtable
 * ----------------------
 * Crea una nuova tabella hash vuota con il numero specificato di bucket.
 *
 * Parametri:
 *   size: numero di bucket della tabella hash.
 *
 * Pre-condizione:
 *   size deve essere maggiore di 0.
 *
 * Post-condizione:
 *   Viene restituita una nuova tabella hash con tutti i bucket inizializzati a NULL.
 *   In caso di errore di allocazione memoria, il programma termina.
 *
 * Ritorna:
 *   Puntatore alla nuova tabella hash creata.
 */
hashtable newHashtable(int size);

/*
 * Funzione: insertHash
 * --------------------
 * Inserisce un nuovo elemento nella tabella hash. Se l'elemento è già presente,
 * l'inserimento non viene effettuato.
 *
 * Parametri:
 *   h: tabella hash di destinazione.
 *   x: elemento da inserire.
 *
 * Pre-condizione:
 *   h deve essere diverso da NULL;
 *   x deve essere diverso da NULL;
 *   getID(x) deve restituire una stringa valida.
 *
 * Post-condizione:
 *   Se elemento non presente: viene inserito in testa alla lista del bucket appropriato;
 *   Se elemento già presente: la tabella rimane invariata.
 *
 * Ritorna:
 *   1 se l'inserimento è riuscito, 0 se l'elemento era già presente.
 */
int insertHash(hashtable h, Iscritto x);

/*
 * Funzione: hashDelete
 * --------------------
 * Rimuove un elemento dalla tabella hash basandosi sulla chiave fornita.
 *
 * Parametri:
 *   h: tabella hash da cui rimuovere l'elemento.
 *   key: chiave dell'elemento da rimuovere.
 *
 * Pre-condizione:
 *   h deve essere diverso da NULL;
 *   key deve essere diverso da NULL.
 *
 * Post-condizione:
 *   Se elemento presente: viene rimosso dalla tabella e i collegamenti della lista vengono aggiornati;
 *   Se elemento non presente: la tabella rimane invariata.
 *   La memoria dell'elemento rimosso NON viene liberata automaticamente.
 *
 * Ritorna:
 *   Puntatore all'elemento rimosso se trovato, NULL se non presente.
 */
Iscritto hashDelete(hashtable h, string key);

/*
 * Funzione: destroyHashtable
 * --------------------------
 * Distrugge completamente una tabella hash liberando tutta la memoria associata.
 *
 * Parametri:
 *   h: tabella hash da distruggere.
 *
 * Pre-condizione:
 *   Nessuna (gestisce il caso h == NULL).
 *
 * Post-condizione:
 *   Tutta la memoria associata alla tabella viene liberata;
 *   Tutti gli elementi contenuti vengono liberati;
 *   Il puntatore h diventa invalido.
 *
 * Ritorna:
 *   Nulla (void).
 */
void destroyHashtable(hashtable h);

/*
 * Funzione: hashSearch
 * --------------------
 * Cerca un elemento nella tabella hash utilizzando la sua chiave (ID).
 *
 * Parametri:
 *   h: tabella hash in cui effettuare la ricerca.
 *   key: chiave dell'elemento da cercare.
 *
 * Pre-condizione:
 *   Nessuna (gestisce parametri NULL).
 *
 * Post-condizione:
 *   La tabella rimane invariata;
 *   Se elemento presente: restituisce puntatore all'elemento;
 *   Se elemento non presente o parametri invalidi: restituisce NULL.
 *
 * Ritorna:
 *   Puntatore all'elemento trovato, NULL se non presente o parametri invalidi.
 */
Iscritto hashSearch(hashtable h, string key);
/*
 * Funzione: ricercaGenerica
 * -------------------------
 * Effettua una ricerca generica nella tabella hash per diversi campi
 * (nome, cognome, durata abbonamento).
 *
 * Parametri:
 *   h: tabella hash in cui effettuare la ricerca.
 *   sel: selettore del campo (0=nome, 1=cognome, 2=durata abbonamento).
 *   str: valore da cercare come stringa.
 *
 * Pre-condizione:
 *   h deve essere diverso da NULL;
 *   sel deve essere 0, 1, o 2;
 *   str deve essere diverso da NULL.
 *
 * Post-condizione:
 *   Stampa automaticamente gli elementi trovati;
 *   Per sel=0,1: controlla anche la validità dell'abbonamento;
 *   Per sel=2: converte str in intero per il confronto.
 *
 * Ritorna:
 *   1 se elemento trovato e valido (abbonamento attivo),
 *   0 se elemento non trovato,
 *   -1 se elemento trovato ma abbonamento scaduto (solo per sel=0,1).
 */
int ricercaGenerica(hashtable h, int sel, string str);
/*
 * Funzione: stampaHash
 * --------------------
 * Stampa tutti gli elementi della tabella hash con tutti i dettagli.
 *
 * Parametri:
 *   h: tabella hash da stampare.
 *
 * Pre-condizione:
 *   Nessuna (gestisce il caso h == NULL).
 *
 * Post-condizione:
 *   Stampa tutti gli elementi con dettagli completi su stdout;
 *   Se tabella vuota, stampa messaggio appropriato;
 *   L'ordine di stampa dipende dall'ordine di hashing.
 *
 * Ritorna:
 *   Nulla (void).
 */
void stampaHash(hashtable h);
/*
 * Funzione: stampaHashMinima
 * --------------------------
 * Stampa una versione compatta di tutti gli elementi della tabella hash
 * (solo ID, cognome, nome).
 *
 * Parametri:
 *   h: tabella hash da stampare.
 *
 * Pre-condizione:
 *   Nessuna (gestisce il caso h == NULL).
 *
 * Post-condizione:
 *   Stampa tabella formattata con intestazioni;
 *   Mostra solo informazioni essenziali per panoramica rapida;
 *   Se tabella vuota, stampa messaggio appropriato.
 *
 * Ritorna:
 *   Nulla (void).
 */
void stampaHashMinima(hashtable h);
/*
 * Funzione: scriviFileClienti
 * ---------------------------
 * Salva tutti i clienti della tabella hash sul file "iscritti.txt".
 *
 * Parametri:
 *   h: tabella hash da salvare su file.
 *
 * Pre-condizione:
 *   h deve essere diverso da NULL;
 *   Devono essere presenti i permessi di scrittura nella directory corrente.
 *
 * Post-condizione:
 *   Crea/sovrascrive il file "iscritti.txt";
 *   Scrive tutti gli elementi della tabella nel file;
 *   In caso di errore di apertura file, il programma termina.
 *
 * Ritorna:
 *   Nulla (void).
 */
void scriviFileClienti(hashtable h);

#endif