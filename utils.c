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

string generaIDCliente(){
  IDCounterCliente++;
  string IDCliente=malloc(sizeof(char)*7);
  if(IDCliente==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  snprintf(IDCliente, 7, "CLT%03d", IDCounterCliente);
  return IDCliente;
}

string generaIDPrenotazione(){
  IDCounterPrenotazione++;
  string IDPrenotazione=malloc(sizeof(char)*7);
  if(IDPrenotazione==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  snprintf(IDPrenotazione, 7, "PRT%03d", IDCounterPrenotazione);
  return IDPrenotazione;
}
string generaIDCorso(){
  IDCounterCorso++;
  string IDCorso=malloc(sizeof(char)*7);
  if(IDCorso==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  snprintf(IDCorso, 7, "CRS%03d", IDCounterCorso);
  return IDCorso;
}

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
  /*Tengo traccia dell'ultimo ID caricato del corso
   *in modo da poter continuare la generazione di ID che
   *verranno poi inseriti a mano
   */

  IDCounterCorso=maxIDCorso;

  fclose(fp);
  free(nome);
  free(ID);
}

void pulisciSchermo(){
  #ifdef _WIN32
    system("cls"); //per Windows
  #else
    system("clear"); // per altri SO
  #endif
}

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