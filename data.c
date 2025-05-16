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
  //Precondizione
  //Controllo validità della data
  while(giorno<=0||giorno>31||mese<=0||mese>12){
    printf("Data non valida\n");
    printf("Inserisci la nuova data (GG/MM/AAAA):\n");
    scanf("%d/%d/%d",&giorno,&mese,&anno);
  }

  //Creazione e Allocazione Data
  Data data;
  data=malloc(sizeof(struct data));
  if(data==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  //Inizializzazione data
  data->giorno=giorno;
  data->mese=mese;
  data->anno=anno;
  return data;
}

Data calcoloDataScadenza(Data data, int durata){
  //PreCondizione
  if(data==NULL||durata<=0){
    printf("Valori Errati\n");
    return NULL;
  }
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
  //Precondizione
  if(dataOriginale==NULL){
    printf("Valori inesistenti\n");
    return NULL;
  }
  Data d=malloc(sizeof(struct data));
  if(d==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }
  d->giorno=dataOriginale->giorno;
  d->mese=dataOriginale->mese;
  d->anno=dataOriginale->anno;
  return d;
}
void stampaData(Data data){
  if(data==NULL){
    printf("Valori inesistenti\n");
    return;
  }
  printf("%d/%d/%d\n",data->giorno,data->mese,data->anno);
}

int getGiorno(Data data){
  if(data==NULL){
    printf("Valori inesistenti\n");
    return -1;
  }
  return data->giorno;
}

int getMese(Data data){
  if(data==NULL){
    printf("Valori inesistenti\n");
    return -1;
  }
  return data->mese;
}

int getAnno(Data data){
  if(data==NULL){
    printf("Valori inesistenti\n");
    return -1;
  }
  return data->anno;
}
int confrontaData(Data d1, Data d2){// -1 se d1 < d2, 0 se d1 == d2, 1 se d1 > d2
  if(d1==NULL||d2==NULL){
    printf("Valori inesistenti\n");
    exit(1);
  }
  if(d1->anno > d2->anno)
    return 1;
  if(d1->anno < d2->anno)
    return -1;

  // Anno uguale, confronto i mesi
  if(d1->mese > d2->mese)
    return 1;
  if(d1->mese < d2->mese)
    return -1;

  // Mese uguale, confronto i giorni
  if(d1->giorno > d2->giorno)
    return 1;
  if(d1->giorno < d2->giorno)
    return -1;

  // Tutti uguali
  return 0;
}