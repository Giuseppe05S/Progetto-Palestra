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
    string orario;
    int numPartecipanti;
};

Corso CreaCorso(string ID, string nome, Data dataLezione, string orario){
    Corso co=malloc(sizeof(struct corso));
    if(co==NULL){
        printf("Errore allocazione memoria\n");
        exit(1);
    }

    co->ID=malloc(sizeof(char)*10);
    co->nome=malloc(sizeof(char)*20);
    co->orario=malloc(sizeof(char)*6);
    co->dataLezione=malloc(sizeof(struct data));

    if(co->nome==NULL || co->orario==NULL || co->ID==NULL || co->dataLezione==NULL){
      printf("Errore allocazione memoria\n");
      exit(1);
    }

    strcpy(co->ID,ID);
    strcpy(co->nome,nome);
    copiaData(co->dataLezione, dataLezione);
    strcpy(co->orario,orario);
    co->numPartecipanti=0;

    return co;
}

void stampaCorso(Corso co){
  printf("ID: %s\n", co->ID);
  printf("Nome: %s\n", co->nome);
  stampaData(co->dataLezione);
  printf("Orario: %s\n", co->orario);
  printf("Numero Partecipanti: %d\n", co->numPartecipanti);
}

int Disponibilita(Corso co){
  if(co->numPartecipanti<maxPartecipanti)
    return 1;
  else
     return 0;
}