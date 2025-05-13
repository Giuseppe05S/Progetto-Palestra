//
// Created by Giuseppe on 28/04/2025.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "iscritto.h"
#include "data.h"
#include "liste.h"
#include "hash.h"

static int IDCounterCorso=0;
static int IDCounterCliente=0;

string generaIDCliente(){
  IDCounterCliente++;
  string IDCliente=malloc(sizeof(char)*7);
  if(IDCliente==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  snprintf(IDCliente, 7, "CLT%03d", IDCounterCliente);
  return IDCliente;
}

string generaIDCorso(){
  IDCounterCorso++;
  string IDCorso=malloc(sizeof(char)*7);
  if(IDCorso==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  snprintf(IDCorso, 7, "CRS%03d", IDCounterCorso);
  return IDCorso;
}

void caricaFileClienti(hashtable h){
  FILE *fp;
  fp=fopen("iscritti.txt","r");
  if(fp==NULL){
    printf("Errore apertura file\n");
    exit(0);
  }

  string nome=malloc(sizeof(char)*50);
  string cognome=malloc(sizeof(char)*50);
  string ID=malloc(sizeof(char)*10);
  if(nome==NULL || cognome==NULL || ID==NULL){
    printf("Errore nell'Allocazione\n");
    exit(0);
  }

  int gg,mm,anno;
  Data dataIscrizione;
  int durata;
  Iscritto isc;

  while(fscanf(fp,"%s%s%s%d%d%d%d", ID, nome, cognome, &gg, &mm, &anno, &durata) != EOF){
    dataIscrizione=creaData(gg,mm,anno);
    isc=CreaIscritto(nome,cognome,dataIscrizione,durata,ID);

    if(insertHash(h,isc)==0){
      printf("Errore nell'inserimento\n");
      exit(0);
    }

  }
  /*Tengo traccia dell'ultimo ID caricato dal cliente
   *in modo da poter continuare la generazione di id che
   *verranno poi inseriti a mano
   */
  IDCounterCliente=atoi(ID+3);

  fclose(fp);
  free(nome);
  free(cognome);
  free(ID);
}

void caricaFileCorso(list l){
  FILE *fp;
  fp=fopen("corsi.txt","r");
  if(fp==NULL){
    printf("Errore apertura file\n");
    exit(0);
  }
  int gg,mm,anno;
  string ID=malloc(sizeof(char)*10);
  string nome=malloc(sizeof(char)*50);
  Data dataLezione;
  string orario=malloc(sizeof(char)*6);
  if(ID==NULL || nome==NULL || orario==NULL){
    printf("Errore nell'Allocazione\n");
    exit(0);
  }

  Corso newCorso;

  while(fscanf(fp,"%s%s%d%d%d%s", ID, nome, &gg, &mm, &anno, orario) != EOF){
    dataLezione=creaData(gg,mm,anno);
    newCorso=creaCorso(ID,nome,dataLezione,orario);
    if(insertList(l,0,newCorso)==0){
      printf("Errore nell'inserimento\n");
      exit(0);
    }
  }
  /*Tengo traccia dell'ultimo ID caricato del corso
   *in modo da poter continuare la generazione di ID che
   *verranno poi inseriti a mano
   */

  IDCounterCorso=atoi(ID+3);

  fclose(fp);
  free(nome);
  free(orario);
  free(ID);
}