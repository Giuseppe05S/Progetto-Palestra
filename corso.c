//
// Created by Giuseppe on 28/04/2025.
//

#include "corso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "data.h"
#define maxPartecipanti 20

struct corso{
    string ID;
    string nome;
    Data dataLezione;
    Orario oraLezione;
    int numPartecipanti;
};
struct orario{
  int ora;
  int minuti;
};

/*
 * Funzione: creaOrario
 * ---------------------------------
 * Crea e inizializza una nuova struttura Orario con i valori di ora e minuti specificati.
 *
 * Parametri:
 *   ora: valore dell'ora (deve essere compreso tra 0 e 23)
 *   minuti: valore dei minuti (deve essere compreso tra 0 e 59)
 *
 * Pre-condizioni:
 *   ora deve essere compresa tra 0 e 23
 *   minuti deve essere compreso tra 0 e 59
 *
 * Post-condizione:
 *   Restituisce un puntatore valido alla struttura Orario creata, NULL in caso di errore di allocazione
 *
 * Come funziona:
 *   - Alloca dinamicamente memoria per la struttura orario
 *   - Inizializza i campi ora e minuti con i valori passati
 *   - Restituisce il puntatore alla struttura creata
 */
Orario creaOrario(int ora,int minuti){
  //ora e minuti controllati in creaCorso
  Orario o=malloc(sizeof(struct orario));
  if(o==NULL){
    printf("Errore allocazione memoria\n");
    return NULL;
  }
  o->ora=ora;
  o->minuti=minuti;
  return o;
}

/*
 * Funzione: creaCorso
 * ---------------------------------
 * Crea e inizializza una nuova struttura Corso con tutti i parametri specificati.
 *
 * Parametri:
 *   ID: identificativo univoco del corso (stringa non NULL)
 *   nome: nome del corso (stringa non NULL)
 *   dataLezione: data della lezione (puntatore Data valido)
 *   ora: ora della lezione (0-23)
 *   minuti: minuti della lezione (0-59)
 *   nPartecipanti: numero attuale di partecipanti (>=0)
 *
 * Pre-condizioni:
 *   ID != NULL
 *   nome != NULL
 *   dataLezione != NULL
 *   0 <= ora < 24
 *   0 <= minuti < 60
 *   nPartecipanti >= 0
 *
 * Post-condizione:
 *   Restituisce un puntatore valido al Corso creato se tutti i parametri sono validi,
 *   NULL altrimenti
 *
 * Come funziona:
 *   - Verifica tutte le precondizioni sui parametri
 *   - Alloca memoria per la struttura corso
 *   - Alloca memoria per i campi stringa ID e nome
 *   - Copia i dati passati come parametri
 *   - Crea l'orario associato tramite creaOrario()
 *   - Copia la data tramite copiaData()
 *   - Restituisce il corso creato o NULL in caso di errore
 */
Corso creaCorso(string ID, string nome, Data dataLezione, int ora,int minuti,int nPartecipanti){
  //Precondizione
  if(ID==NULL||nome==NULL||dataLezione==NULL||(ora<0||ora>=24)||(minuti<0||minuti>=60)||nPartecipanti<0){
    return NULL;
  }

  Corso co=malloc(sizeof(struct corso));
  if(co==NULL){
    printf("Errore allocazione memoria\n");
    return NULL;
  }

  co->ID=malloc(sizeof(char)*10);
  co->nome=malloc(sizeof(char)*20);
  if(co->nome==NULL || co->ID==NULL){
    printf("Errore allocazione memoria\n");
    return NULL;
  }

  strcpy(co->ID,ID);
  strcpy(co->nome,nome);
  co->dataLezione=copiaData(dataLezione);
  co->oraLezione=creaOrario(ora,minuti);
  co->numPartecipanti=nPartecipanti;

  if(co->oraLezione==NULL){
    printf("Errore nella creazione di Orario\n");
    return NULL;
  }

  return co;
}

/*
 * Funzione: stampaCorso
 * ---------------------------------
 * Stampa tutte le informazioni del corso in formato dettagliato, solo se il corso è disponibile.
 *
 * Parametri:
 *   co: puntatore al corso da stampare
 *
 * Pre-condizioni:
 *   co può essere NULL (viene gestito dalla funzione)
 *
 * Post-condizione:
 *   Le informazioni del corso vengono stampate su stdout se il corso è valido e disponibile
 *
 * Come funziona:
 *   - Verifica che il corso non sia NULL
 *   - Controlla la disponibilità del corso tramite Disponibilita()
 *   - Stampa tutti i dettagli del corso in formato strutturato con separatori
 *   - Include ID, nome, data, orario e numero partecipanti
 */
void stampaCorso(Corso co){
  //Precondizione
  if(co==NULL){
    printf("Il corso non esiste\n");
    return;
  }
  if(Disponibilita(co)){
      printf("==============================\n");
      printf("ID: %s\n", co->ID);
      printf("Nome: %s\n", co->nome);
      printf("Data Lezione: ");
      stampaData(co->dataLezione);
      printf("Orario: %02d:%02d\n", co->oraLezione->ora,co->oraLezione->minuti);
      printf("Numero Partecipanti: %d\n", co->numPartecipanti);
  }
}
/*
 * Funzione: stampaCorsoEssenziale
 * ---------------------------------
 * Stampa le informazioni essenziali del corso in formato compatto su una singola riga.
 *
 * Parametri:
 *   co: puntatore al corso da stampare
 *
 * Pre-condizioni:
 *   co può essere NULL (viene gestito dalla funzione)
 *
 * Post-condizione:
 *   Le informazioni essenziali del corso vengono stampate su stdout se il corso è valido e disponibile
 *
 * Come funziona:
 *   - Verifica che il corso non sia NULL
 *   - Controlla la disponibilità del corso
 *   - Stampa ID, nome, data e orario in formato tabulare compatto
 *   - Utilizza formattazione con larghezza fissa per allineamento
 */
void stampaCorsoEssenziale(Corso co){
  //Precondizione
  if(co==NULL){
    printf("Il corso non esiste\n");
    return;
  }
  if(Disponibilita(co)){
    printf("%-8s %-12s %02d/%02d/%04d   %02d:%02d\n",co->ID,co->nome,getGiorno(co->dataLezione),getMese(co->dataLezione),getAnno(co->dataLezione),co->oraLezione->ora,co->oraLezione->minuti);
  }
}
/*
 * Funzione: getIDCorso
 * ---------------------------------
 * Restituisce l'ID del corso specificato.
 *
 * Parametri:
 *   co: puntatore al corso di cui ottenere l'ID
 *
 * Pre-condizioni:
 *   co può essere NULL (viene gestito dalla funzione)
 *
 * Post-condizione:
 *   Restituisce il puntatore alla stringa ID se il corso è valido, NULL altrimenti
 *
 * Come funziona:
 *   - Verifica che il corso non sia NULL
 *   - Restituisce il puntatore al campo ID della struttura
 */
string getIDCorso(Corso co){
  if(co==NULL){
    printf("Il corso non esiste\n");
    return NULL;
  }
  return co->ID;
}
/*
 * Funzione: getNomeCorso
 * ---------------------------------
 * Restituisce il nome del corso specificato.
 *
 * Parametri:
 *   co: puntatore al corso di cui ottenere il nome
 *
 * Pre-condizioni:
 *   co può essere NULL (viene gestito dalla funzione)
 *
 * Post-condizione:
 *   Restituisce il puntatore alla stringa nome se il corso è valido, NULL altrimenti
 *
 * Come funziona:
 *   - Verifica che il corso non sia NULL
 *   - Restituisce il puntatore al campo nome della struttura
 */
string getNomeCorso(Corso co){
  if(co==NULL){
    printf("Il corso non esiste\n");
    return NULL;
  }
  return co->nome;
}
/*
 * Funzione: getDataCorso
 * ---------------------------------
 * Restituisce la data della lezione del corso specificato.
 *
 * Parametri:
 *   co: puntatore al corso di cui ottenere la data
 *
 * Pre-condizioni:
 *   co può essere NULL (viene gestito dalla funzione)
 *
 * Post-condizione:
 *   Restituisce il puntatore alla Data se il corso è valido, NULL altrimenti
 *
 * Come funziona:
 *   - Verifica che il corso non sia NULL
 *   - Restituisce il puntatore al campo dataLezione della struttura
 */
Data getDataCorso(Corso co){
  if(co==NULL){
    printf("Il corso non esiste\n");
    return NULL;
  }
  return co->dataLezione;
}
/*
 * Funzione: getNumPartecipantiCorso
 * ---------------------------------
 * Restituisce il numero di partecipanti del corso specificato.
 *
 * Parametri:
 *   co: puntatore al corso di cui ottenere il numero di partecipanti
 *
 * Pre-condizioni:
 *   co può essere NULL (viene gestito dalla funzione)
 *
 * Post-condizione:
 *   Restituisce il numero di partecipanti se il corso è valido, 0 altrimenti
 *
 * Come funziona:
 *   - Verifica che il corso non sia NULL
 *   - Restituisce il valore del campo numPartecipanti
 */
int getNumPartecipantiCorso(Corso co){
if(co==NULL){
    printf("Il corso non esiste\n");
    return 0;
  }
  return co->numPartecipanti;
}
/*
 * Funzione: confrontaOrario
 * ---------------------------------
 * Confronta due orari e restituisce il risultato del confronto.
 *
 * Parametri:
 *   o1: primo orario da confrontare
 *   o2: secondo orario da confrontare
 *
 * Pre-condizioni:
 *   o1 e o2 devono essere puntatori validi (non NULL)
 *
 * Post-condizione:
 *   Restituisce -1 se o1 < o2, 0 se o1 == o2, 1 se o1 > o2
 *
 * Come funziona:
 *   - Verifica che entrambi gli orari non siano NULL
 *   - Confronta prima le ore: se diverse, restituisce il risultato
 *   - Se le ore sono uguali, confronta i minuti
 *   - Restituisce -1, 0 o 1 in base al confronto
 */
int confrontaOrario(Orario o1, Orario o2){ // -1 se o1< o2, 0 se o1== o2, 1 se o1> o2
  if(o1 == NULL || o2 == NULL){
    printf("Errore: uno dei due orari è NULL.\n");
    return 0;
  }
  // Confronta le ore
  if (o1->ora < o2->ora){
    return -1;  // o1 è prima
  }else if (o1->ora > o2->ora){
    return 1;   // o1 è dopo
  }else{
    // Ore uguali, confronto minuti
    if (o1->minuti < o2->minuti){
      return -1; // o1 è prima
    }else if (o1->minuti > o2->minuti){
      return 1;  // o1 è dopo
    }else{
      return 0;  // orari identici
    }
  }
}
/*
 * Funzione: getOrario
 * ---------------------------------
 * Restituisce l'orario della lezione del corso specificato.
 *
 * Parametri:
 *   co: puntatore al corso di cui ottenere l'orario
 *
 * Pre-condizioni:
 *   co può essere NULL (viene gestito dalla funzione)
 *
 * Post-condizione:
 *   Restituisce il puntatore all'Orario se il corso è valido, NULL altrimenti
 *
 * Come funziona:
 *   - Verifica che il corso non sia NULL
 *   - Restituisce il puntatore al campo oraLezione della struttura
 */
Orario getOrario(Corso co){
  if(co==NULL){
    printf("Il corso non esiste\n");
    return NULL;
  }
  return co->oraLezione;
}
/*
 * Funzione: incrementaPartecipanti
 * ---------------------------------
 * Incrementa di uno il numero di partecipanti del corso specificato.
 *
 * Parametri:
 *   co: puntatore al corso di cui incrementare i partecipanti
 *
 * Pre-condizioni:
 *   co può essere NULL (viene gestito dalla funzione)
 *
 * Post-condizione:
 *   Il numero di partecipanti del corso viene incrementato di 1 se il corso è valido
 *
 * Come funziona:
 *   - Verifica che il corso non sia NULL
 *   - Incrementa il campo numPartecipanti di 1
 */
void incrementaPartecipanti(Corso co){
	if(co==NULL){
	printf("Il corso non esiste\n");
	return;
	}
	co->numPartecipanti++;
}
/*
 * Funzione: decrementaPartecipanti
 * ---------------------------------
 * Decrementa di uno il numero di partecipanti del corso specificato.
 *
 * Parametri:
 *   co: puntatore al corso di cui decrementare i partecipanti
 *
 * Pre-condizioni:
 *   co può essere NULL (viene gestito dalla funzione)
 *
 * Post-condizione:
 *   Il numero di partecipanti del corso viene decrementato di 1 se il corso è valido
 *
 * Come funziona:
 *   - Verifica che il corso non sia NULL
 *   - Decrementa il campo numPartecipanti di 1
 */
void decrementaPartecipanti(Corso co){
  if(co==NULL){
    printf("Il corso non esiste\n");
    return;
  }
  co->numPartecipanti--;
}
/*
 * Funzione: scriviCorso
 * ---------------------------------
 * Scrive le informazioni del corso su file in formato strutturato.
 *
 * Parametri:
 *   co: puntatore al corso da scrivere su file
 *   fp: puntatore al file su cui scrivere
 *
 * Pre-condizioni:
 *   co deve essere un puntatore valido a una struttura corso
 *   fp deve essere un puntatore valido a un file aperto in modalità scrittura
 *
 * Post-condizione:
 *   I dati del corso vengono scritti sul file specificato
 *
 * Come funziona:
 *   - Utilizza fprintf per scrivere tutti i campi del corso
 *   - Formato: ID nome giorno mese anno ora:minuti numPartecipanti
 *   - Ogni corso viene scritto su una riga separata
 */
void scriviCorso(Corso co,FILE *fp){
  fprintf(fp,"%s %s %d %d %d %02d:%02d %d\n",co->ID,co->nome,getGiorno(co->dataLezione),getMese(co->dataLezione),getAnno(co->dataLezione),co->oraLezione->ora,co->oraLezione->minuti,co->numPartecipanti);
}
/*
 * Funzione: Disponibilita
 * ---------------------------------
 * Verifica se il corso ha ancora posti disponibili confrontando il numero attuale
 * di partecipanti con il limite massimo.
 *
 * Parametri:
 *   co: puntatore al corso di cui verificare la disponibilità
 *
 * Pre-condizioni:
 *   co deve essere un puntatore valido a una struttura corso
 *
 * Post-condizione:
 *   Restituisce 1 se ci sono posti disponibili (numPartecipanti < maxPartecipanti),
 *   0 se il corso è al completo
 *
 * Come funziona:
 *   - Confronta il numero attuale di partecipanti con maxPartecipanti (20)
 *   - Restituisce 1 se c'è disponibilità, 0 se il corso è pieno
 */
int Disponibilita(Corso co){
  if(co->numPartecipanti<maxPartecipanti)
    return 1;
  else
     return 0;
}