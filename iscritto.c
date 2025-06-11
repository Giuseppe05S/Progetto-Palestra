//
// Created by Giuseppe on 28/04/2025.
//
//#include "utils.h"
#include "iscritto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

struct iscritto{
  string ID;
  string nome;
  string cognome;
  Data dataIscrizione;
  Data dataScadenza;
  int durata; //espressa in Mesi
  Iscritto next;
};
/*
•  Funzione: CreaIscritto
•  -----------------------------------
•  Crea e inizializza un nuovo iscritto con i dati forniti.
*
•  Parametri:
*   nome: nome dell'iscritto.
*   cognome: cognome dell'iscritto.
*   dataIscrizione: data di iscrizione dell'iscritto.
*   durata: durata dell'abbonamento in mesi.
*   ID: identificativo univoco dell'iscritto.
*
•  Pre-condizione:
*   Tutti i parametri devono essere validi e non NULL.
*   durata deve essere un valore positivo.
*   ID deve essere una stringa di massimo 6 caratteri.
*
•  Post-condizione:
*   Viene creato un nuovo iscritto con tutti i campi inizializzati.
*   La data di scadenza viene calcolata automaticamente.
*   Il campo next viene inizializzato a NULL.
*   Restituisce il puntatore al nuovo iscritto.
*
•  Come funziona:
•  - Alloca memoria per la struttura iscritto.
•  - Alloca memoria dinamica per nome, cognome e ID.
•  - Copia i dati forniti nei campi della struttura.
•  - Copia la data di iscrizione usando copiaData.
•  - Calcola la data di scadenza basandosi su iscrizione e durata.
•  - Inizializza il puntatore next a NULL.
•  - Restituisce il puntatore al nuovo iscritto creato.
*/
Iscritto CreaIscritto(string nome, string cognome, Data dataIscrizione, int durata,string ID){
  if(nome==NULL||cognome==NULL||dataIscrizione==NULL||durata<1||ID==NULL){
    printf("Valori sbagliati o inesistenti\n");
    return NULL;
  }
  	Iscritto is=malloc(sizeof(struct iscritto));
  	if(is==NULL){
    	printf("Errore allocazione memoria\n");
    	return NULL;
  	}

    is->nome=malloc(strlen(nome)+1);
    is->cognome=malloc(strlen(cognome)+1);
    is->ID=malloc(sizeof(char)*7);
    if(is->nome==NULL || is->cognome==NULL || is->ID==NULL){
      printf("Errore allocazione memoria\n");
      return NULL;
    }
	//Data viene creata prima
  	//Controlla data prima di invocare CreaIscritto
  	//quindi nell'ADT LIST
  	strcpy(is->nome,nome);
  	strcpy(is->cognome,cognome);
    is->dataIscrizione=copiaData(dataIscrizione);
  	is->dataScadenza=calcoloDataScadenza(dataIscrizione,durata);
  	is->durata=durata;
  	strcpy(is->ID,ID);
    is->next=NULL;
    if(is->dataIscrizione==NULL||is->dataScadenza==NULL){
      printf("Errore nella data\n");
      return NULL;
    }
	return is;
}
/*
•  Funzione: getNext
•  -----------------------------------
•  Restituisce il puntatore al prossimo iscritto nella lista.
*
•  Parametri:
*   is: iscritto di cui ottenere il successore.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Restituisce il puntatore al prossimo iscritto.
*   Può restituire NULL se non c'è un successore.
*
•  Come funziona:
•  - Accede al campo next della struttura iscritto.
•  - Restituisce direttamente il valore del puntatore next.
*/
Iscritto getNext(Iscritto is){
  if(is==NULL){
    printf("Il cliente non esiste\n");
    exit(1);
  }
  return is->next;
}
/*
•  Funzione: getID
•  -----------------------------------
•  Restituisce l'ID dell'iscritto.
*
•  Parametri:
*   is: iscritto di cui ottenere l'ID.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Restituisce una stringa contenente l'ID dell'iscritto.
*   La stringa restituita non deve essere modificata.
*
•  Come funziona:
•  - Accede al campo ID della struttura iscritto.
•  - Restituisce il puntatore alla stringa ID.
*/
string getID(Iscritto is){
  if(is==NULL){
    printf("Il cliente non esiste\n");
    exit(1);
  }
  return is->ID;
}
/*
•  Funzione: getNome
•  -----------------------------------
•  Restituisce il nome dell'iscritto.
*
•  Parametri:
*   is: iscritto di cui ottenere il nome.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Restituisce una stringa contenente il nome dell'iscritto.
*   La stringa restituita non deve essere modificata.
*
•  Come funziona:
•  - Accede al campo nome della struttura iscritto.
•  - Restituisce il puntatore alla stringa nome.
*/
string getNome(Iscritto is){
  if(is==NULL){
    printf("Il cliente non esiste\n");
    exit(1);
  }
  return is->nome;
}
/*
•  Funzione: getCognome
•  -----------------------------------
•  Restituisce il cognome dell'iscritto.
*
•  Parametri:
*   is: iscritto di cui ottenere il cognome.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Restituisce una stringa contenente il cognome dell'iscritto.
*   La stringa restituita non deve essere modificata.
*
•  Come funziona:
•  - Accede al campo cognome della struttura iscritto.
•  - Restituisce il puntatore alla stringa cognome.
*/
string getCognome(Iscritto is){
  if(is==NULL){
    printf("Il cliente non esiste\n");
    exit(1);
  }
  return is->cognome;
}
/*
•  Funzione: getDurata
•  -----------------------------------
•  Restituisce la durata dell'abbonamento dell'iscritto.
*
•  Parametri:
*   is: iscritto di cui ottenere la durata abbonamento.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Restituisce un intero rappresentante la durata in mesi.
*   Il valore restituito è sempre non negativo.
*
•  Come funziona:
•  - Accede al campo durata della struttura iscritto.
•  - Restituisce il valore intero della durata.
*/
int getDurata(Iscritto is){
  if(is==NULL){
    printf("Il cliente non esiste\n");
    exit(1);
  }
  return is->durata;
}
/*
-  Funzione: getDataScadenza
-  -------------------------
-  Restituisce la data di scadenza dell'abbonamento di un iscritto.
*
-  Parametri:
*   is: puntatore all'oggetto Iscritto di cui si vuole ottenere la data di scadenza.
*
-  Pre-condizione:
*   is deve essere un puntatore valido e non NULL a un oggetto Iscritto inizializzato.
*
-  Post-condizione:
*   Viene restituita la data di scadenza dell'abbonamento dell'iscritto.
*   Se is è NULL, stampa un messaggio di errore e termina il programma.
*
-  Come funziona:
-  - Verifica che il puntatore is non sia NULL.
-  - Se è NULL, stampa un messaggio di errore e termina l'esecuzione.
-  - Restituisce il campo dataScadenza dell'oggetto Iscritto.
*/
Data getDataScadenza(Iscritto is){
  if(is==NULL){
    printf("Il cliente non esiste\n");
    exit(1);
  }
  return is->dataScadenza;
}
/*
•  Funzione: setNext
•  -----------------------------------
•  Imposta il puntatore al prossimo iscritto nella lista.
*
•  Parametri:
*   is: iscritto a cui impostare il successore.
*   next: puntatore al prossimo iscritto.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*   next può essere un puntatore valido o NULL.
*
•  Post-condizione:
*   Il campo next dell'iscritto viene aggiornato con il nuovo valore.
*   La lista collegata viene modificata di conseguenza.
*
•  Come funziona:
•  - Accede al campo next della struttura iscritto.
•  - Assegna il nuovo valore al campo next.
*/
void setNext(Iscritto is, Iscritto next){
  if(is==NULL){
    printf("Il cliente non esiste\n");
    exit(1);
  }
  is->next=next;
}
/*
•  Funzione: eliminaIscritto
•  -----------------------------------
•  Elimina completamente un iscritto liberando tutta la memoria allocata.
*
•  Parametri:
*   is: iscritto da eliminare.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*   Tutti i campi dell'iscritto devono essere stati allocati correttamente.
*
•  Post-condizione:
*   Tutta la memoria allocata per l'iscritto viene liberata.
*   Il puntatore is non è più valido dopo questa operazione.
*
•  Come funziona:
•  - Libera la memoria allocata per l'ID.
•  - Libera la memoria allocata per il nome.
•  - Libera la memoria allocata per il cognome.
•  - Libera la memoria allocata per la data di iscrizione.
•  - Libera la memoria allocata per la data di scadenza.
•  - Libera la memoria della struttura iscritto principale.
*/
void eliminaIscritto(Iscritto is){
  if(is==NULL){
    printf("Il cliente non esiste\n");
    exit(1);
  }
  free(is->ID);
  free(is->nome);
  free(is->cognome);
  free(is->dataIscrizione);
  free(is->dataScadenza);
  free(is);
}
/*
•  Funzione: rinnovaAbbonamento
•  -----------------------------------
•  Rinnova l'abbonamento di un iscritto estendendo la durata.
*
•  Parametri:
*   is: iscritto a cui rinnovare l'abbonamento.
*   durata: mesi aggiuntivi di abbonamento.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*   durata deve essere un valore positivo maggiore di 0.
*
•  Post-condizione:
*   La durata totale dell'abbonamento viene incrementata.
*   La data di scadenza viene ricalcolata automaticamente.
*   Se i parametri non sono validi, stampa un messaggio di errore.
*
•  Come funziona:
•  - Verifica la validità dei parametri di input.
•  - Incrementa la durata totale dell'abbonamento.
•  - Ricalcola la data di scadenza basandosi sulla nuova durata.
•  - Utilizza la data di iscrizione originale come riferimento.
*/
void rinnovaAbbonamento(Iscritto is, int durata){
  //Precondizione
  if(is==NULL||durata<=0){
    printf("DATI NON VALIDI\n");
    return;
  }
  is->durata+=durata;
  is->dataScadenza=calcoloDataScadenza(is->dataIscrizione,is->durata);
  if(is->dataScadenza==NULL){
    printf("Errore nella Data\n");
    exit(1);
  }
}
/*
•  Funzione: stampaMinimaCliente
•  -----------------------------------
•  Stampa le informazioni essenziali di un iscritto in formato tabellare.
*
•  Parametri:
*   is: iscritto di cui stampare le informazioni.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Vengono stampate ID, cognome e nome in formato allineato.
*   La stampa è compatibile con intestazioni tabellari.
*
•  Come funziona:
•  - Utilizza printf con formattazione a larghezza fissa.
•  - Stampa ID con larghezza 8 caratteri allineato a sinistra.
•  - Stampa cognome con larghezza 15 caratteri allineato a sinistra.
•  - Stampa nome con larghezza 15 caratteri allineato a sinistra.
*/
void stampaMinimaCliente(Iscritto is){
  if(is==NULL){
    printf("Il cliente non esiste\n");
    exit(1);
  }
  printf("%-8s %-15s %-15s\n",is->ID,is->cognome,is->nome);
}
/*
•  Funzione: controlloAbbonamento
•  -----------------------------------
•  Verifica se l'abbonamento di un iscritto è ancora valido.
*
•  Parametri:
*   is: iscritto di cui controllare l'abbonamento.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Restituisce 0 se l'abbonamento è valido.
*   Restituisce 1 se l'abbonamento è scaduto.
*   Restituisce -1 se i dati non sono validi.
*
•  Come funziona:
•  - Verifica la validità del puntatore e della durata.
•  - Confronta la data di scadenza con la data odierna.
•  - Utilizza confrontaData per determinare se è scaduto.
•  - Restituisce un codice di stato appropriato.
*/
int controlloAbbonamento(Iscritto is){
  if(is==NULL){
    printf("DATI NON VALIDI\n");
    exit(1);
  }
  if(confrontaData(is->dataScadenza,dataOggi())==-1){
    return 1;//Abbonamento Scaduto
  }
  return 0;//Abbonamento Valido
}
/*
•  Funzione: stampaCliente
•  -----------------------------------
•  Stampa tutte le informazioni dettagliate di un iscritto.
*
•  Parametri:
*   is: iscritto di cui stampare le informazioni complete.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*
•  Post-condizione:
*   Vengono stampate tutte le informazioni dell'iscritto.
*   La stampa include separatori per una migliore leggibilità.
*
•  Come funziona:
•  - Stampa un separatore visivo per delimitare le informazioni.
•  - Stampa ID, nome e cognome con etichette descrittive.
•  - Stampa la data di iscrizione utilizzando stampaData.
•  - Stampa la durata dell'abbonamento in mesi.
•  - Stampa la data di scadenza utilizzando stampaData.
*/
void stampaCliente(Iscritto is){
  if(is==NULL){
    printf("Il cliente non esiste\n");
    exit(1);
  }
  printf("==============================\n");
  printf("ID: %s\n",is->ID);
  printf("Nome: %s\n",is->nome);
  printf("Cognome: %s\n",is->cognome);
  printf("Data di Iscrizione: ");
  stampaData(is->dataIscrizione);
  printf("Durata Abbonamento: %d Mesi\n", is->durata);
  printf("Data di Scadenza: ");
  stampaData(is->dataScadenza);
}
/*
•  Funzione: scriviCliente
•  -----------------------------------
•  Scrive le informazioni di un iscritto su file in formato strutturato.
*
•  Parametri:
*   is: iscritto di cui scrivere le informazioni.
*   fp: puntatore al file aperto in modalità scrittura.
*
•  Pre-condizione:
*   is deve essere un puntatore valido a un iscritto.
*   fp deve essere un file aperto e valido per la scrittura.
*
•  Post-condizione:
*   I dati dell'iscritto vengono scritti nel file in formato testo.
*   I campi sono separati da spazi per facilitare la lettura.
*
•  Come funziona:
•  - Utilizza fprintf per scrivere nel file specificato.
•  - Scrive ID, nome e cognome come stringhe.
•  - Estrae e scrive giorno, mese e anno della data di iscrizione.
•  - Scrive la durata dell'abbonamento come intero.
•  - Tutti i campi sono separati da spazi e terminati da newline.
*/
void scriviCliente(Iscritto is,FILE *fp){
  fprintf(fp,"%s %s %s %d %d %d %d\n",is->ID,is->nome,is->cognome,getGiorno(is->dataIscrizione),getMese(is->dataIscrizione),getAnno(is->dataIscrizione),is->durata);
}