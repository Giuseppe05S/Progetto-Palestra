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

void calcolaDataScadenza(Data data, int durata){
  int scarto;

  Data scadenza;
  scadenza=malloc(sizeof(Data));
  if(scadenza==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  //Gestione rinnovo in anno successivo
  if((data->mese+durata)>12){
    scarto=(data->mese+durata)-12;
    data->mese=scarto;
    data->anno++;
  }
}

void stampaData(Data data){
  printf("%d/%d/%d\n",data->giorno,data->mese,data->anno);
}