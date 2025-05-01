//
// Created by Giuseppe on 28/04/2025.
//

#include "iscritto.h"
#include <stdio.h>
#include "utils.h"
#include "data.h"

struct iscritto{
  string nome;
  string cognome;
  Data dataIscrizione;
  Data dataScadenza;
  int durata; //espressa in Mesi
  string ID;
};

Iscritto CreaIscritto(string nome, string cognome, Data dataIscrizione, int durata, string ID){

  Iscritto is=malloc(sizeof(Iscritto));
  if(is==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }
  //Controlla data prima di invocare CreaIscritto
  //quindi nell'ADT LIST
  is->nome=nome;
  is->cognome=cognome;
  is->dataIscrizione=dataIscrizione;
  is->dataScadenza=calcoloDataScadenza(Iscrizione,durata);
  is->durata=durata;
  is->ID=ID;

  return is;
}