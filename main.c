//
// Created by Giuseppe on 28/04/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iscritto.h"
#include "data.h"
#include "liste.h"
#include "utils.h"
#include "hash.h"

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
    pulisciSchermo();
    printf("Gestore Prenotazioni\n");
    printf("1. Prenota Corso\n");
    printf("2. Ricerca Prenotazione\n");
    printf("3. Elenco Prenotazione\n");
    printf("4. Elimina Prenotazione\n");
    printf("5. Torna al Menù\n");
    scanf("%c",&selP);

    switch(selP){
      case '1':
        pulisciSchermo();
        string IDCliente=malloc(sizeof(char)*7);
        string IDCorso=malloc(sizeof(char)*7);
        Data dPrenotazione;
        int gg,mm,anno;

        printf("==============================\n");
        printf("\tAGGIUNGI PRENOTAZIONE\n");
        printf("==============================\n");

        printf("Inserisci l'ID del cliente\n");
        scanf("%s",IDCliente);

        printf("Inserisci la data della prenotazione(GG/MM/AAAA):\n");
        scanf("%d/%d/%d",&gg,&mm,&anno);
        dPrenotazione=creaData(gg,mm,anno);
           /*chiediamo l'id cliente
             stampiamo i corsi disponibili
            chiediamo l'ID del corso da prenotare
            Data=oggi
            creiamo la prenotazione
            */
        break;
      case '2':
      pulisciSchermo();
      string IDClienteRicerca = malloc(sizeof(char)*7);
      if(IDClienteRicerca == NULL){
        printf("Errore allocazione memoria\n");
        exit(1);
      }

      printf("==============================\n");
      printf("\tRICERCA PRENOTAZIONE\n");
      printf("==============================\n");

      printf("Inserisci l'ID del cliente:\n");
      scanf("%s", IDClienteRicerca);

        break;
      case '3':
            //scorri la coda e stampi tutte le prenotazioni di un determinato utente
      pulisciSchermo();
      printf("==============================\n");
      printf("\tELENCO PRENOTAZIONI\n");
      printf("==============================\n");
        break;
      case '4':
        pulisciSchermo();
      printf("==============================\n");
      printf("\tELIMINA PRENOTAZIONE\n");
      printf("==============================\n");

      string IDPrenotazioneDaEliminare = malloc(sizeof(char)*7);
      if(IDPrenotazioneDaEliminare == NULL){
        printf("Errore allocazione memoria\n");
        exit(1);
      }

      printf("Inserisci l'ID della prenotazione da eliminare:\n");
      scanf("%s", IDPrenotazioneDaEliminare);
        // scorri la coda affinche non trovi la prenotazione da cancellare
        break;
      case '5':

        break;
      default:
        printf("Scelta non valida \n");
        break;
    }
    if(selP=='5')
      break;
  }while(selP>'5'||selP<'1');
}

void menuAbbonamento(hashtable h){
  string ID=malloc(sizeof(char)*7);
  /* DA SPOSTARE TUTTE LE DICHIARAZIONI ALL'ESTERNO DEL DO WHILE*/
  char selA;
  do{
    getchar();
    pulisciSchermo();
    printf("Gestore Abbonamenti\n");
    printf("1. Crea Abbonamento\n");
    printf("2. Rinnova Abbonamento\n");
    printf("3. Ricerca Abbonamento\n");
    printf("4. Elenco Abbonamenti\n");
    printf("5. Elimina Abbonamento\n");
    printf("6. Torna al Menù\n");
    scanf("%c",&selA);

    switch(selA){
      case '1':
        pulisciSchermo();
        Iscritto isc;
        string nome=malloc(sizeof(char)*50);
        string cognome=malloc(sizeof(char)*50);


        if(nome==NULL || cognome==NULL || ID==NULL){
          printf("Errore nell'Allocazione\n");
          exit(0);
        }

        int durata,gg,mm,anno;
        Data dataIscrizione;

        printf("==============================\n");
        printf("\tAGGIUNGI CLIENTE\n");
        printf("==============================\n");
        printf("Inserisci nome\n");
        scanf("%s",nome);
        printf("Inserisci cognome\n");
        scanf("%s",cognome);

        printf("Inserisci la data d'iscrizione(GG/MM/AAAA):\n");
        scanf("%d/%d/%d",&gg,&mm,&anno);
        dataIscrizione=creaData(gg,mm,anno);
        printf("Inserisci la durata dell'abbonamento in mesi (ES. 1, 3, 6, ...)\n");
        scanf("%d",&durata);

        strcpy(ID,generaIDCliente());
        isc=CreaIscritto(nome,cognome,dataIscrizione,durata,ID);
        printf("\n==============================\n");
        printf("\tCLIENTE AGGIUNTO\n");
        stampaCliente(isc);
        if(insertHash(h,isc)==0){
          printf("Errore nell'inserimento\n");
        }
        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
      case '2':
        pulisciSchermo();
        printf("==============================\n");
        printf("\tRINNOVO ABBONAMENTO\n");
        printf("==============================\n");
        Iscritto is;
        int nuovaDurata;
        printf("Inserisci l'ID del Cliente\n");
        stampaHashMinima(h);
        scanf("%s",ID);
        is=hashSearch(h,ID);

        do{
        printf("Di quanti mesi vuoi espandere l'abbonamento?\n");
        scanf("%d",&nuovaDurata);
        }while(nuovaDurata<0);

        rinnovaAbbonamento(is,nuovaDurata);
        printf("==============================\n");
        printf("\tCLIENTE AGGIORNATO\n");
        stampaCliente(is);
        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
      case '3':
        pulisciSchermo();



        printf("Premere invio per tornare indietro\n");
        getchar();
        break;
      case '4':
        pulisciSchermo();

        stampaHash(h);

        printf("Premere invio per tornare indietro\n");
        getchar();
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

void menuCorso(list listaCorsi) {
  char selC;
  do {
    getchar();
    pulisciSchermo();
    printf("Gestore Corsi\n");
    printf("1. Aggiungi Corso\n");
    printf("2. Ricerca Corso\n");
    printf("3. Elenco Corsi\n");
    printf("4. Elimina Corso\n");
    printf("5. Torna al Menù\n");
    scanf("%c", &selC);

    switch(selC) {
      case '1': {
        pulisciSchermo();
        printf("==============================\n");
        printf("\tAGGIUNGI CORSO\n");
        printf("==============================\n");

        string nome = malloc(sizeof(char) * 50);
        string IDCorso = malloc(sizeof(char) * 7);
        int durata;
        if (nome == NULL || IDCorso == NULL) {
          printf("Errore allocazione memoria\n");
          exit(1);
        }

        printf("Inserisci il nome del corso:\n");
        scanf("%s", nome);

        strcpy(IDCorso, generaIDCorso());

        printf("\n==============================\n");
        printf("\tCORSO AGGIUNTO\n");
        stampaCorso(c);
        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
      }

      case '2': {
        pulisciSchermo();
        printf("==============================\n");
        printf("\tRICERCA CORSO\n");
        printf("==============================\n");

        string IDRicerca = malloc(sizeof(char) * 7);
        if (IDRicerca == NULL) {
          printf("Errore allocazione memoria\n");
          exit(1);
        }

        printf("Inserisci l'ID del corso:\n");
        scanf("%s", IDRicerca);

        break;
      }

      case '3':
        pulisciSchermo();
        printf("==============================\n");
        printf("\tELENCO CORSI\n");
        printf("==============================\n");
        stampaLista(listaCorsi);
        printf("Premere invio per tornare indietro\n");
        getchar();
        break;

      case '4': {
        pulisciSchermo();
        printf("==============================\n");
        printf("\tELIMINA CORSO\n");
        printf("==============================\n");
        string IDDaEliminare = malloc(sizeof(char) * 7);
        if (IDDaEliminare == NULL) {
          printf("Errore allocazione memoria\n");
          exit(1);
        }
        printf("Inserisci l'ID del corso da eliminare:\n");
        scanf("%s", IDDaEliminare);
        listaCorsi = eliminaCorso(listaCorsi, IDDaEliminare); // funzione da implementare
        printf("Premere invio per tornare indietro\n");
        getchar();
        break;
      }

      case '5':
        break;

      default:
        printf("Scelta non valida \n");
        break;
    }

    if(selC == '5')
      break;
  } while(selC < '1' || selC > '5');
}

int main(){

  hashtable hClienti=newHashtable(30);
  list listaCorsi=newList();

  caricaFileClienti(hClienti);
  caricaFileCorso(listaCorsi);

  listaCorsi=reverseList(listaCorsi);

  stampaLista(listaCorsi);

  char selettore;
  do{
    pulisciSchermo();
    printf("Gestore Palestra\n");
    printf("1. Gestione Abbonamenti\n");
    printf("2. Gestione Prenotazione\n");
    printf("3. Esci\n");
    scanf("%c",&selettore);

    switch(selettore){
      case '1':
        menuAbbonamento(hClienti);
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