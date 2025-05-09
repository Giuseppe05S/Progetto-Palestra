//
// Created by Giuseppe on 28/04/2025.
//

#include "iscritto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "data.h"

static int idCounter;

struct iscritto{
  string ID;
  string nome;
  string cognome;
  Data dataIscrizione;
  Data dataScadenza;
  int durata; //espressa in Mesi
  Iscritto next;
};

string generaID(){
  idCounter++;
  string IDCliente=malloc(sizeof(char)*7);
  if(IDCliente==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  snprintf(IDCliente, 7, "USR%03d", idCounter);
  return IDCliente;
}

Iscritto CreaIscritto(string nome, string cognome, Data dataIscrizione, int durata){
  	Iscritto is=malloc(sizeof(Iscritto));
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
	copiaData(is->dataIscrizione, dataIscrizione);
  	is->dataScadenza=calcoloDataScadenza(dataIscrizione,durata);
  	is->durata=durata;
  	strcpy(is->ID,generaID());

	return is;
}

Iscritto getNext(Iscritto is){
  return is->next;
}
string getID(Iscritto is){
  return is->ID;
}
void setNext(Iscritto is, Iscritto next){
  is->next=next;
}
void setIDCounter(int counter){
      idCounter=counter;
}
void stampaCliente(Iscritto is){
  printf("ID: %s\n",is->ID);
  printf("Nome: %s\n",is->nome);
  printf("Cognome: %s\n",is->cognome);
  stampaData(is->dataIscrizione);
  stampaData(is->dataScadenza);
}