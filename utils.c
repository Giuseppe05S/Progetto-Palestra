//
// Created by Giuseppe on 28/04/2025.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "iscritto.h"
#include "prenotazione.h"
#include "listaPrenotazione.h"
#include "data.h"
#include "liste.h"
#include "hash.h"

static int IDCounterCorso=0;
static int IDCounterPrenotazione=0;
static int IDCounterCliente=0;
/*
• Funzione: generaIDCliente
• -----------------------------------
• Genera un nuovo ID univoco per un cliente nel formato "CLT###".
*
• Post-condizione:
* Ritorna una stringa allocata dinamicamente contenente il nuovo ID cliente.
*
• Come funziona:
• - Incrementa il contatore globale degli ID cliente.
• - Alloca memoria per la stringa dell’ID.
• - Usa snprintf per creare l’ID nel formato "CLT###".
• - Restituisce la stringa generata.
*/
string generaIDCliente(){
  //incremento il contatore, dato che l'ultimo salvato è gia utilizzato
  IDCounterCliente++;
  string IDCliente=malloc(sizeof(char)*7);
  if(IDCliente==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  snprintf(IDCliente, 7, "CLT%03d", IDCounterCliente);
  return IDCliente;
}
/*
• Funzione: generaIDPrenotazione
• -----------------------------------
• Genera un nuovo ID univoco per una prenotazione nel formato "PRT###".
*
• Post-condizione:
* Ritorna una stringa allocata dinamicamente contenente il nuovo ID prenotazione.
*
• Come funziona:
• - Incrementa il contatore globale degli ID prenotazione.
• - Alloca memoria per la stringa.
• - Crea l’ID con snprintf nel formato "PRT###".
• - Restituisce la stringa.
*/
string generaIDPrenotazione(){
  //incremento il contatore, dato che l'ultimo salvato è gia utilizzato
  IDCounterPrenotazione++;
  string IDPrenotazione=malloc(sizeof(char)*7);
  if(IDPrenotazione==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  snprintf(IDPrenotazione, 7, "PRT%03d", IDCounterPrenotazione);
  return IDPrenotazione;
}
/*
• Funzione: generaIDCorso
• -----------------------------------
• Genera un nuovo ID univoco per un corso nel formato "CRS###".
*
• Post-condizione:
* Ritorna una stringa allocata dinamicamente contenente il nuovo ID corso.
*
• Come funziona:
• - Incrementa il contatore globale degli ID corso.
• - Alloca memoria per la stringa.
• - Usa snprintf per generare la stringa "CRS###".
• - Restituisce l’ID.
*/
string generaIDCorso(){
  //incremento il contatore, dato che l'ultimo salvato è gia utilizzato
  IDCounterCorso++;
  string IDCorso=malloc(sizeof(char)*7);
  if(IDCorso==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  snprintf(IDCorso, 7, "CRS%03d", IDCounterCorso);
  return IDCorso;
}
/*
• Funzione: caricaFileClienti
• -----------------------------------
• Carica da file tutte le informazioni relative agli iscritti (clienti)
• e le inserisce in una hashtable.
*
• Parametri:
*   h: hashtable dove inserire gli iscritti.
*
• Pre-condizione:
*  Il file "iscritti.txt" deve esistere e contenere dati validi.
*  La hashtable deve essere inizializzata.
*
• Post-condizione:
*  La hashtable viene popolata con tutti gli iscritti presenti nel file.
*  Il contatore globale degli ID cliente viene aggiornato.
*
• Come funziona:
• - Apre il file "iscritti.txt".
• - Legge riga per riga i dati degli iscritti.
• - Crea gli oggetti Iscritto e li inserisce nella hashtable.
• - Tiene traccia del massimo ID cliente per aggiornare il contatore.
• - Libera la memoria e chiude il file.
*/
void caricaFileClienti(hashtable h){
  FILE *fp;
  static int maxIDCliente=0;
  int temp;
  fp=fopen("iscritti.txt","r");
  if(fp==NULL){
    printf("Errore apertura file iscritti\n");
    exit(0);
  }

  string nome=malloc(sizeof(char)*50);
  string cognome=malloc(sizeof(char)*50);
  string ID=malloc(sizeof(char)*10);
  if(nome==NULL || cognome==NULL || ID==NULL){
    printf("Errore nell'Allocazione\n");
    exit(0);
  }

  int gg,mm,anno;
  Data dataIscrizione;
  int durata;
  Iscritto isc;

  while(fscanf(fp,"%s%s%s%d%d%d%d", ID, nome, cognome, &gg, &mm, &anno, &durata) != EOF){
    dataIscrizione=creaData(gg,mm,anno);
    isc=CreaIscritto(nome,cognome,dataIscrizione,durata,ID);
    if(isc==NULL){
      printf("Errore nella creazione di iscritto\n");
      exit(0);
    }
    if(insertHash(h,isc)==0){
      printf("Errore nell'inserimento\n");
      exit(0);
    }
	  temp=atoi(ID+3);
  	if(temp>maxIDCliente){
    	maxIDCliente=temp;
 	  }
  }

  IDCounterCliente=maxIDCliente;

  fclose(fp);
  free(nome);
  free(cognome);
  free(ID);
}
/*
• Funzione: caricaFileCorso
• -----------------------------------
• Carica tutti i corsi da file e li inserisce in una lista.
*
• Parametri:
*  l: lista dove inserire i corsi caricati.
*
• Pre-condizione:
*  Il file "corsi.txt" deve essere presente e valido.
*  La lista deve essere inizializzata.
*
• Post-condizione:
*  I corsi vengono inseriti nella lista.
*  Il contatore globale degli ID corso viene aggiornato.
*
• Come funziona:
• - Apre il file "corsi.txt".
• - Legge i dati di ogni corso: ID, nome, data, ora, partecipanti.
• - Crea gli oggetti Corso e li inserisce nella lista.
• - Aggiorna il contatore ID corso se necessario.
• - Libera memoria e chiude il file.
*/
void caricaFileCorso(list l){
  static int maxIDCorso=0;
  int temp;
  FILE *fp;
  fp=fopen("corsi.txt","r");
  if(fp==NULL){
    printf("Errore apertura file corsi\n");
    exit(0);
  }
  int gg,mm,anno;
  string ID=malloc(sizeof(char)*10);
  string nome=malloc(sizeof(char)*50);
  Data dataLezione;
  int ora,minuti;
  int nPartecipanti;
  if(ID==NULL || nome==NULL){
    printf("Errore nell'Allocazione\n");
    exit(0);
  }

  Corso newCorso;

  while(fscanf(fp,"%s%s%d%d%d%d:%d%d", ID, nome, &gg, &mm, &anno, &ora, &minuti,&nPartecipanti) != EOF){
    dataLezione=creaData(gg,mm,anno);
    newCorso=creaCorso(ID,nome,dataLezione,ora,minuti,nPartecipanti);
    if(newCorso==NULL){
      printf("Errore nella creazione di corso\n");
      exit(0);
    }
    if(insertList(l,0,newCorso)==0){
      printf("Errore nell'inserimento\n");
      exit(0);
    }
    temp=atoi(ID+3);
  	if(temp>maxIDCorso){
    	maxIDCorso=temp;
 	}
  }

  IDCounterCorso=maxIDCorso;

  fclose(fp);
  free(nome);
  free(ID);
}
/*
• Funzione: pulisciSchermo
• -----------------------------------
• Pulisce lo schermo della console, in modo cross-platform.
*
• Post-condizione:
*  La schermata del terminale viene ripulita.
*
• Come funziona:
• - Verifica se il sistema operativo è Windows o Unix-like.
• - Esegue il comando di sistema appropriato ("cls" o "clear").
*/
void pulisciSchermo(){
  #ifdef _WIN32
    system("cls"); //per Windows
  #else
    system("clear"); // per altri SO
  #endif
}
/*
• Funzione: caricaFilePrenotazioni
• -----------------------------------
• Carica tutte le prenotazioni da file e le inserisce in una lista.
*
• Parametri:
*  l: lista di prenotazioni dove inserire i dati letti dal file.
*
• Pre-condizione:
*  Il file "prenotazioni.txt" deve essere presente e corretto.
*  La lista deve essere inizializzata.
*
• Post-condizione:
*  Tutte le prenotazioni vengono aggiunte alla lista.
*  Il contatore globale degli ID prenotazione viene aggiornato.
*
• Come funziona:
• - Apre il file "prenotazioni.txt".
• - Legge ID prenotazione, ID corso, ID cliente e la data.
• - Crea oggetti Prenotazione e li inserisce nella lista.
• - Tiene traccia dell’ID massimo per aggiornare il contatore.
• - Libera memoria e chiude il file.
*/
void caricaFilePrenotazioni(listP l){
  static int maxIDPrenotazione=0;
  int temp;
  FILE *fp;
  fp=fopen("prenotazioni.txt","r");
  if(fp==NULL){
    printf("Errore apertura file prenotazioni\n");
    exit(0);
  }
  int gg,mm,anno;
  string IDPrenotazione=malloc(sizeof(char)*10);
  string IDCorso=malloc(sizeof(char)*10);
  string IDCliente=malloc(sizeof(char)*10);
  Data dataPrenotazione;

  if(IDPrenotazione==NULL || IDCorso==NULL|| IDCliente==NULL){
    printf("Errore nell'Allocazione\n");
    exit(0);
  }

  Prenotazione newPrenotazione;

  while(fscanf(fp,"%s%s%s%d%d%d", IDPrenotazione,IDCorso,IDCliente,&gg, &mm, &anno) != EOF){
    dataPrenotazione=creaData(gg,mm,anno);
    newPrenotazione=creaPrenotazione(IDPrenotazione,IDCorso,IDCliente,dataPrenotazione);
    if(newPrenotazione==NULL){
      printf("Errore nella creazione della prenotazione\n");
      exit(0);
    }
    if(insertListPrenotati(l,0,newPrenotazione)==0){
      printf("Errore nell'inserimento\n");
      exit(0);
    }
    temp=atoi(IDPrenotazione+3);
    if(temp>maxIDPrenotazione){
      maxIDPrenotazione=temp;
    }
  }

  IDCounterPrenotazione=maxIDPrenotazione;

  fclose(fp);
  free(IDPrenotazione);
  free(IDCorso);
  free(IDCliente);
}