//
// Created by Giuseppe on 28/04/2025.
//

#include "corso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "data.h"
#define maxPartecipanti 20

struct corso{
    string ID;
    string nome;
    Data dataLezione;
    Orario oraLezione;
    int numPartecipanti;
};
struct orario{
  int ora;
  int minuti;
};

Orario creaOrario(int ora,int minuti){
  //ora e minuti controllati in creaCorso
  Orario o=malloc(sizeof(struct orario));
  if(o==NULL){
    printf("Errore allocazione memoria\n");
    return NULL;
  }
  o->ora=ora;
  o->minuti=minuti;
  return o;
}

Corso creaCorso(string ID, string nome, Data dataLezione, int ora,int minuti,int nPartecipanti){
  //Precondizione
  if(ID==NULL||nome==NULL||dataLezione==NULL||(ora<0||ora>=24)||(minuti<0||minuti>=60)||nPartecipanti<0){
    return NULL;
  }

  Corso co=malloc(sizeof(struct corso));
  if(co==NULL){
    printf("Errore allocazione memoria\n");
    return NULL;
  }

  co->ID=malloc(sizeof(char)*10);
  co->nome=malloc(sizeof(char)*20);
  if(co->nome==NULL || co->ID==NULL){
    printf("Errore allocazione memoria\n");
    return NULL;
  }

  strcpy(co->ID,ID);
  strcpy(co->nome,nome);
  co->dataLezione=copiaData(dataLezione);
  co->oraLezione=creaOrario(ora,minuti);
  co->numPartecipanti=nPartecipanti;

  if(co->oraLezione==NULL){
    printf("Errore nella creazione di Orario\n");
    return NULL;
  }

  return co;
}

void stampaCorso(Corso co){
  //Precondizione
  if(co==NULL){
    printf("Il corso non esiste\n");
    return;
  }
  if(Disponibilita(co)){
      printf("==============================\n");
      printf("ID: %s\n", co->ID);
      printf("Nome: %s\n", co->nome);
      printf("Data Lezione: ");
      stampaData(co->dataLezione);
      printf("Orario: %02d:%02d\n", co->oraLezione->ora,co->oraLezione->minuti);
      printf("Numero Partecipanti: %d\n", co->numPartecipanti);
  }
}
string getIDCorso(Corso co){
  if(co==NULL){
    printf("Il corso non esiste\n");
    return NULL;
  }
  return co->ID;
}
string getNomeCorso(Corso co){
  if(co==NULL){
    printf("Il corso non esiste\n");
    return NULL;
  }
  return co->nome;
}
Data getDataCorso(Corso co){
  if(co==NULL){
    printf("Il corso non esiste\n");
    return NULL;
  }
  return co->dataLezione;
}
int confrontaOrario(Orario o1, Orario o2){ // -1 se o1< o2, 0 se o1== o2, 1 se o1> o2
  if(o1 == NULL || o2 == NULL){
    printf("Errore: uno dei due orari è NULL.\n");
    return 0;
  }
  // Confronta le ore
  if (o1->ora < o2->ora){
    return -1;  // o1 è prima
  }else if (o1->ora > o2->ora){
    return 1;   // o1 è dopo
  }else{
    // Ore uguali, confronto minuti
    if (o1->minuti < o2->minuti){
      return -1; // o1 è prima
    }else if (o1->minuti > o2->minuti){
      return 1;  // o1 è dopo
    }else{
      return 0;  // orari identici
    }
  }
}
Orario getOrario(Corso co){
  if(co==NULL){
    printf("Il corso non esiste\n");
    return NULL;
  }
  return co->oraLezione;
}
void incrementaPartecipanti(Corso co){
	if(co==NULL){
	printf("Il corso non esiste\n");
	return;
	}
	co->numPartecipanti++;
}
void scriviCorso(Corso co,FILE *fp){
  fprintf(fp,"%s %s %d %d %d %02d:%02d %d\n",co->ID,co->nome,getGiorno(co->dataLezione),getMese(co->dataLezione),getAnno(co->dataLezione),co->oraLezione->ora,co->oraLezione->minuti,co->numPartecipanti);
}
int Disponibilita(Corso co){
  if(co->numPartecipanti<maxPartecipanti)
    return 1;
  else
     return 0;
}