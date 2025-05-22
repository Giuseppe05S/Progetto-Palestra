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

  Prenotazione pr;

  pr=malloc(sizeof(struct prenotazione));
  pr->IDPrenotazione=malloc(strlen(IDPrenotazione)+1);
  pr->IDCorso=malloc(strlen(IDCorso)+1);
  pr->IDCliente=malloc(strlen(IDCliente)+1);
  //da verificare se allocare la data
  if(pr->IDPrenotazione==NULL || pr->IDCorso==NULL || pr->IDCliente==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  strcpy(pr->IDPrenotazione,IDPrenotazione);
  strcpy(pr->IDCorso,IDCorso);
  strcpy(pr->IDCliente,IDCliente);
  pr->dataPrenotazione=copiaData(dataPrenotazione);

  return pr;
}

void eliminaPrenotazione(Prenotazione pr){
  free(pr->IDPrenotazione);
  free(pr->IDCorso);
  free(pr->IDCliente);
  free(pr->dataPrenotazione);
  free(pr);
}

Data getDataPrenotazione(Prenotazione pr){
  return pr->dataPrenotazione;
}
string getIDCorsoPrenotazione(Prenotazione pr){
  return pr->IDCorso;
}
string getIDClientePrenotazione(Prenotazione pr){
  return pr->IDCliente;
}
void stampaPrenotazione(Prenotazione p){
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