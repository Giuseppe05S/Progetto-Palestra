//
// Created by Giuseppe on 28/04/2025.
//

#include "prenotazione.h"
#include "corso.h"
#include "iscritto.h"
#include "data.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct prenotazione{
  string IDPrenotazione;
  string IDCorso;
  string IDCliente;
  Data dataPrenotazione;
};


Prenotazione creaPrenotazione(string IDPrenotazione, string IDCorso, string IDCliente, Data dataPrenotazione){
  if(IDPrenotazione == NULL||IDCorso == NULL||IDCliente == NULL||dataPrenotazione == NULL){
    printf("Valori sbagliati o inesistenti\n");
    return NULL;
  }
  Prenotazione pr;

  pr=malloc(sizeof(struct prenotazione));
  pr->IDPrenotazione=malloc(strlen(IDPrenotazione)+1);
  pr->IDCorso=malloc(strlen(IDCorso)+1);
  pr->IDCliente=malloc(strlen(IDCliente)+1);

  if(pr->IDPrenotazione==NULL || pr->IDCorso==NULL || pr->IDCliente==NULL){
    printf("Errore allocazione memoria\n");
    return NULL;
  }

  strcpy(pr->IDPrenotazione,IDPrenotazione);
  strcpy(pr->IDCorso,IDCorso);
  strcpy(pr->IDCliente,IDCliente);
  pr->dataPrenotazione=copiaData(dataPrenotazione);
  if(pr->dataPrenotazione==NULL){
    printf("Errore nella data\n");
    return NULL;
  }

  return pr;
}

void eliminaPrenotazione(Prenotazione pr){
  if(pr==NULL){
    printf("La prenotazione non esiste\n");
    return;
  }
  free(pr->IDPrenotazione);
  free(pr->IDCorso);
  free(pr->IDCliente);
  free(pr->dataPrenotazione);
  free(pr);
}

Data getDataPrenotazione(Prenotazione pr){
  if(pr==NULL){
    printf("La prenotazione non esiste\n");
    exit(1);
  }
  return pr->dataPrenotazione;
}
string getIDCorsoPrenotazione(Prenotazione pr){
  if(pr==NULL){
    printf("La prenotazione non esiste\n");
    exit(1);
  }
  return pr->IDCorso;
}
string getIDClientePrenotazione(Prenotazione pr){
  if(pr==NULL){
    printf("La prenotazione non esiste\n");
    exit(1);
  }
  return pr->IDCliente;
}
string getIDPrenotazione(Prenotazione pr){
  if(pr==NULL){
    printf("La prenotazione non esiste\n");
    exit(1);
  }
  return pr->IDPrenotazione;
}
void stampaPrenotazione(Prenotazione p){
  if(p==NULL){
    printf("La prenotazione non esiste\n");
    return;
  }
  printf("==============================\n");
  printf("ID Prenotazione: %s\n", p->IDPrenotazione);
  printf("ID Corso: %s\n",p->IDCorso);
  printf("ID Cliente: %s\n",p->IDCliente);
  printf("Data Prenotazione: ");
  stampaData(p->dataPrenotazione);
}

void scriviPrenotazione(Prenotazione p,FILE *fp){
  fprintf(fp,"%s %s %s %d %d %d\n",p->IDPrenotazione,p->IDCorso,p->IDCliente,getGiorno(p->dataPrenotazione),getMese(p->dataPrenotazione),getAnno(p->dataPrenotazione));
}