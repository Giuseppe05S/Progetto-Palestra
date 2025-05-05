//
// Created by Giuseppe on 28/04/2025.
//

#include "corso.h"

struct corso{
    string ID;
    string nome;
    Data dataLezione;
    string oario;
    int Maxpartecipanti=20;
    int Numpartecipanti;
};

Corso CreaCorso(string ID, string nome, Data dataLezione, string orario){
    Corso co=malloc(sizeof(Corso));
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