//
// Created by Giuseppe on 28/04/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "iscritto.h"
#include "data.h"
#include "liste.h"
#include "utils.h"
#include "hash.h"

static int idCouter=0;

string generaID(){
  idCouter++;
  string IDCliente=malloc(sizeof(char)*7);
  if(IDCliente==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  snprintf(IDCliente, 7, "CLT%03d", idCounter);
  return IDCliente;
  free(IDCliente);
}

void caricaFileIscritti(hashtable h){
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
    }

  }
  /*Tengo traccia dell'ultimo ID caricato dal cliente
   *in modo da poter continuare la generazione di id che
   *verranno poi inseriti a mano
   */
  idCounter=atoi(ID+3);

  fclose(fp);
  free(nome);
  free(cognome);
  free(ID);
}

int testData(){
	FILE *fp;
	fp=fopen("testDataInput.txt","r");
    if(fp==NULL){
      	printf("Errore apertura file\n");
        return 0;
    }
	int gg,mm,aa,durata;
	Data d[10];
    Data ds[10];
	int i=0,j;
	//Leggo le date e le durate degli abbonamenti dal file
    while(fscanf(fp,"%d%d%d%d",&gg,&mm,&aa,&durata)!=EOF){
		d[i]=creaData(gg,mm,aa);
        ds[i]=calcoloDataScadenza(d[i],durata);
        i++;
    }

	fclose(fp);
    //Verifica delle date lette e delle date calcolate
	for(j=0;j<i;j++){
		stampaData(d[j]);
        stampaData(ds[j]);
	}
	return 1;
}

void menuPrenotazione(){
  char selP;
  do{
    getchar();
    printf("Gestore Prenotazioni\n");
    printf("1. Crea Prenotazione\n");
    printf("2. Modifica Prenotazione\n");
    printf("3. Ricerca Prenotazione\n");
    printf("4. Elenco Prenotazione\n");
    printf("5. Elimina Prenotazione\n");
    printf("6. Torna al Menù\n");
    scanf("%c",&selP);

    switch(selP){
      case '1':
        string IDCliente=malloc(sizeof(char)*50);
        string IDCorso=

        break;
      case '2':

        break;
      case '3':

        break;
      case '4':

        break;
      case '5':

        break;
      case '6':
        break;
      default:
        printf("Scelta non valida \n");
        break;
    }
    if(selP=='6')
      break;
  }while(selP>'6'||selP<'1');
}

void menuAbbonamento(hashtable h){

  char selA;
  do{
    getchar();
    printf("Gestore Abbonamenti\n");
    printf("1. Crea Abbonamento\n");
    printf("2. Modifica Abbonamento\n");
    printf("3. Ricerca Abbonamento\n");
    printf("4. Elenco Abbonamenti\n");
    printf("5. Elimina Abbonamento\n");
    printf("6. Torna al Menù\n");
    scanf("%c",&selA);

    switch(selA){
      case '1':

        Iscritto isc;
        string nome=malloc(sizeof(char)*50);
        string cognome=malloc(sizeof(char)*50);
		string ID=malloc(sizeof(char)*7);

        if(nome==NULL || cognome==NULL || ID==NULL){
          printf("Errore nell'Allocazione\n");
          exit(0);
        }

        int durata,gg,mm,anno;
        Data dataIscrizione;

        printf("Inserisci nome\n");
        scanf("%s",nome);
        printf("Inserisci cognome\n");
        scanf("%s",cognome);

        printf("Inserisci la data d'iscrizione(GG/MM/AAAA):\n");
        scanf("%d/%d/%d",&gg,&mm,&anno);
        dataIscrizione=creaData(gg,mm,anno);
        printf("Inserisci la durata dell'abbonamento in mesi (ES. 1, 3, 6, ...)\n");
        scanf("%d",&durata);

        strcpy(ID,generaID());
        isc=CreaIscritto(nome,cognome,dataIscrizione,durata,ID);

        if(insertHash(h,0,isc)==0){
          printf("Errore nell'inserimento\n");
        }
        break;
      case '2':

        break;
      case '3':

        break;
      case '4':

        break;
      case '5':

        break;
        case '6':
          break;
      default:
        printf("Scelta non valida \n");
        break;
    }
    if(selA=='6')
      break;
  }while(selA>'6'||selA<'1');
}
int main(){

  hashtable h=newHashtable();

  caricaFileIscritti(h);
  stampaHash(h);
  char selettore;
  do{
    printf("Gestore Palestra\n");
    printf("1. Gestione Abbonamenti\n");
    printf("2. Gestione Prenotazione\n");
    printf("3. Esci\n");
    scanf("%c",&selettore);

    switch(selettore){
      case '1':
        menuAbbonamento(h);
        getchar();
        break;
      case '2':
        menuPrenotazione();
        getchar();
        break;
    }
    if(selettore!='1'&&selettore!='2'&&selettore!='3'){
      printf("Scelta non valida \n");
    }
  }while(selettore!='3');
}