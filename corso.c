//
// Created by Giuseppe on 28/04/2025.
//

#include "corso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "data.h"

struct corso{
    string ID;
    string nome;
    Data dataLezione;
    string oario;
    int Maxpartecipanti=20;
    int Numpartecipanti;
};

Corso CreaCorso(string ID, string nome, Data dataLezione, string orario){
    Corso co=malloc(sizeof(corso));
    if(co==NULL){
        printf("Errore allocazione memoria\n");
        exit(1);
    }
    strcpy(co->ID,ID);
    strcpy(co->nome,nome);
    copiaData(co->dataLezione, dataLezione);
    strcpy(co->oario,orario);
    co->Numpartecipanti=0;



    return co;
}

void stampaCorso(Corso co){
  printf("ID: %s\n" co->ID);
  printf("Nome: %s\n" co->nome);
  stampaData(co->dataLezione);
  printf("Oario: %s\n" co->oario);
  printf("Numpartecipanti: %d\n", co->Numppartecipanti);
}

int Disponibilita(Corso co){
  if(co->Numpartecipanti<co->maxpartecipanti)
    return 1
  else
     return 0;
}