//
// Created by Giuseppe on 28/04/2025.
//
#include<stdio.h>
#include<stdlib.h>
#include "data.h"

struct data{
  int giorno;
  int mese;
  int anno;
};


Data creaData(int giorno,int mese,int anno){
  //Creazione e Allocazione Data
  Data data;
  data=malloc(sizeof(struct data));
  if(data==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  //Controllo validità della data
  while(giorno<=0||giorno>31||mese<=0||mese>12){
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

Data calcoloDataScadenza(Data data, int durata){

  Data scadenza;
  scadenza=malloc(sizeof(struct data));
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
Data copiaData(Data dataOriginale){
	Data d=malloc(sizeof(struct data));
	if(d==NULL){
		printf("Errore allocazione memoria\n");
	}
	d->giorno=dataOriginale->giorno;
	d->mese=dataOriginale->mese;
	d->anno=dataOriginale->anno;
}
void stampaData(Data data){
  printf("%d/%d/%d\n",data->giorno,data->mese,data->anno);
}

int getGiorno(Data data){
  return data->giorno;
}

int getMese(Data data){
  return data->mese;
}

int getAnno(Data data){
  return data->anno;
}