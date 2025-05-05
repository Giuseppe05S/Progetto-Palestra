//
// Created by Giuseppe on 28/04/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "iscritto.h"
#include "data.h"
#include "liste.h"
#include "utils.h"

void caricaFileIscritti(list l){
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
    printf("Nome: %s\n", nome);
    printf("Cognome: %s\n", cognome);
    printf("Durata: %d\n", durata);
    printf("ID: %s\n", ID);
    printf("2\n");
    isc=CreaIscritto(nome,cognome,dataIscrizione,durata,ID);
    printf("3\n");
    if(insertList(l,0,isc)==0){
      printf("Errore nell'inserimento\n");
    }
  }
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
void menuAbbonamento(){

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

  list lIscritti=newList();

  caricaFileIscritti(lIscritti);

  char selettore;
  do{
    printf("Gestore Palestra\n");
    printf("1. Gestione Abbonamenti\n");
    printf("2. Gestione Prenotazione\n");
    printf("3. Esci\n");
    scanf("%c",&selettore);

    switch(selettore){
      case '1':
        menuAbbonamento();
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