//
// Created by Giuseppe on 28/04/2025.
//
#include<stdio.h>
#include "data.h"

struct data{
  int giorno;
  int mese;
  int anno;
};


Data creaData(int giorno,int mese,int anno){
  //Creazione e Allocazione Data
  Data data;
  data=malloc(sizeof(data));
  if(data==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  //Controllo validità della data
  while(g<=0||g>31||m<=0||m>12){
    printf("Data inesistente\n");
    printf("Inserisci la nuova data (GG/MM/AAAA):\n");
    scanf("%d/%d/%d",&giorno,&mese,&anno);
  }

  //Inizializzazione data
  data->giorno=giorno;
  data->mese=mese;
  data->anno=anno;
  return data;
}

Data calcolaDataScadenza(Data data, int durata){

  Data scadenza;
  scadenza=malloc(sizeof(Data));
  if(scadenza==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  scadenza->giorno=data->giorno;
  scadenza->mese=data->mese+durata;
  scadenza->anno=data->anno;

  //Gestione rinnovo in anno successivo
  if(scadenza->mese>12){
    scadenza->mese-=12;
    scadenza->anno++;
  }
  return scadenza;
}

void stampaData(Data data){
  printf("%d/%d/%d\n",data->giorno,data->mese,data->anno);
}