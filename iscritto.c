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

Iscritto CreaIscritto(string nome, string cognome, Data dataIscrizione, int durata,string ID){
  	Iscritto is=malloc(sizeof(struct iscritto));
  	if(is==NULL){
    	printf("Errore allocazione memoria\n");
    	exit(1);
  	}

    is->nome=malloc(strlen(nome)+1);
    is->cognome=malloc(strlen(cognome)+1);
    is->ID=malloc(sizeof(char)*7);
    if(is->nome==NULL || is->cognome==NULL || is->ID==NULL){
      printf("Errore allocazione memoria\n");
      exit(1);
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
	return is;
}

Iscritto getNext(Iscritto is){
  return is->next;
}

string getID(Iscritto is){
  return is->ID;
}
string getNome(Iscritto is){
  return is->nome;
}
string getCognome(Iscritto is){
  return is->cognome;
}
int getDurata(Iscritto is){
  return is->durata;
}

void setNext(Iscritto is, Iscritto next){
  is->next=next;
}

void eliminaIscritto(Iscritto is){
  free(is->ID);
  free(is->nome);
  free(is->cognome);
  free(is->dataIscrizione);
  free(is->dataScadenza);
  free(is);
}
void rinnovaAbbonamento(Iscritto is, int durata){
  //Precondizione
  if(is==NULL||durata<=0){
    printf("DATI NON VALIDI\n");
    return;
  }
  is->durata+=durata;
  is->dataScadenza=calcoloDataScadenza(is->dataIscrizione,is->durata);
}

void stampaMinimaCliente(Iscritto is){
  printf("%-8s %-15s %-15s\n",is->ID,is->cognome,is->nome);
}

void stampaCliente(Iscritto is){
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
void scriviCliente(Iscritto is,FILE *fp){
  fprintf(fp,"%s %s %s %d %d %d %d\n",is->ID,is->nome,is->cognome,getGiorno(is->dataIscrizione),getMese(is->dataIscrizione),getAnno(is->dataIscrizione),is->durata);
}