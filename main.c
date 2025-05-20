//
// Created by Giuseppe on 28/04/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iscritto.h"
#include "data.h"
#include "liste.h"
#include "listaPrenotazione.h"
#include "prenotazione.h"
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

void menuPrenotazione(list lCorsi,hashtable hClienti,listP lPrenotati){
  char selP;
  Prenotazione pre;
  list result=newList();
  Iscritto i;
  string IDCliente=malloc(sizeof(char)*7);
  string IDCorso=malloc(sizeof(char)*7);
  string IDPrenotazione=malloc(sizeof(char)*7);
  Data dataPrenotazione;
  int gg,mm,anno;
  if(IDCliente==NULL||IDCorso==NULL||IDPrenotazione==NULL){
    printf("Errore apertura file\n");
    return;
  }
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
      case '1': //da aggiungere l'incremento dei posti occupati del corso
        pulisciSchermo();
		getchar();
        printf("==============================\n");
        printf("    AGGIUNGI PRENOTAZIONE\n");
        printf("==============================\n");

        printf("\nInserisci l'ID del Cliente\n");
		scanf("%s",IDCliente);
		i=hashSearch(hClienti,IDCliente);
        if(i==NULL){
          pulisciSchermo();
		  printf("==============================\n");
          printf("     Cliente non trovato\n");
		  printf("==============================\n");
		  printf("\nPremere invio per tornare indietro\n");
          getchar();
		  break;
        }

  		//printf("%-8s %-15s %-15s\n","ID","Cognome","Nome");
		//stampaMinimaCliente(i);
		stampaCliente(i);
		getchar();
        printf("\nInserisci l'ID del Corso\n");
		scanf("%s",IDCorso);
		result=ricercaGenericaLista(lCorsi,0,IDCorso);
        if(isEmpty(result)==1){
		  pulisciSchermo();
		  printf("==============================\n");
          printf("      Corso non trovato\n");
		  printf("==============================\n");
		  printf("\nPremere invio per tornare indietro\n");
          getchar();
		  break;
        }
		stampaLista(result);
        printf("\nInserisci la data della prenotazione(GG/MM/AAAA):\n");
        scanf("%d/%d/%d",&gg,&mm,&anno);
        dataPrenotazione=creaData(gg,mm,anno);

        strcpy(IDPrenotazione,generaIDPrenotazione());
        pre=creaPrenotazione(IDPrenotazione,IDCorso,IDCliente,dataPrenotazione);

        if(insertListPrenotati(lPrenotati,0,pre)==0){
          printf("Errore nell'Inserimento\n");
		  break;
        }

		pulisciSchermo();
		printf("==============================\n");
        printf("    PRENOTAZIONE AGGIUNTA\n");
		printf("==============================\n");
		stampaPrenotazione(pre);
        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
      case '2':
		pulisciSchermo();

        break;
      case '3':
		pulisciSchermo();

        stampaListaPrenotazioni(lPrenotati);

		printf("\nPremere invio per tornare indietro\n");
        getchar();
		break;
      case '4':
        pulisciSchermo();
		getchar();
		printf("==============================\n");
        printf("\tCANCELLA PRENOTAZIONE\n");
		printf("==============================\n");
		printf("Inserisci l'ID del Cliente\n");
		scanf("%s",IDCliente);

		//Controllo che il cliente esista
		if(hashSearch(hClienti,IDCliente)==NULL){
          pulisciSchermo();
		  printf("==============================\n");
          printf("     Cliente non trovato\n");
		  printf("==============================\n");
		  printf("\nPremere invio per tornare indietro\n");
          return;
        }

/*chiedi l'ID utente
stampi tutte le prenotazioni dell'utente
l'utente scrive ID della prenotazione da cancellare
*/
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

  int durata,gg,mm,anno;
  Data dataIscrizione;
  Iscritto is;
  string nome=malloc(sizeof(char)*50);
  string cognome=malloc(sizeof(char)*50);
  string ID=malloc(sizeof(char)*7);

  if(nome==NULL || cognome==NULL || ID==NULL){
    printf("Errore nell'Allocazione\n");
    exit(0);
  }
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
        is=CreaIscritto(nome,cognome,dataIscrizione,durata,ID);
        printf("\n==============================\n");
        printf("\tCLIENTE AGGIUNTO\n");
        stampaCliente(is);
        if(insertHash(h,is)==0){
          printf("Errore nell'inserimento\n");
        }
        scriviFileClienti(h);
        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
      case '2':
        pulisciSchermo();

        printf("==============================\n");
        printf("\tRINNOVO ABBONAMENTO\n");
        printf("==============================\n");

        int nuovaDurata;
        printf("Inserisci l'ID del Cliente\n");
        stampaHashMinima(h);
        scanf("%s",ID);

        is=hashSearch(h,ID);
        if(is==NULL){
          pulisciSchermo();
          printf("==============================\n");
          printf("Cliente Inesistente\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }

        do{
          printf("Di quanti mesi vuoi espandere l'abbonamento?\n");
          scanf("%d",&nuovaDurata);
        }while(nuovaDurata<0);

        rinnovaAbbonamento(is,nuovaDurata);
        printf("==============================\n");
        printf("\tCLIENTE AGGIORNATO\n");
        stampaCliente(is);
        scriviFileClienti(h);
        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
      case '3':
        char selR;
        do{
          getchar();
          pulisciSchermo();
          printf("==============================\n");
          printf("\tRICERCA ABBONAMENTO\n");
          printf("==============================\n");
          printf("Per cosa vuoi Ricercare?\n");
          printf("1. ID\n");
          printf("2. Nome\n");
          printf("3. Cognome\n");
          printf("4. Durata Abbonamento\n");
          printf("5. Esci\n");
          scanf("%c",&selR);

          switch(selR){
            case '1':
              pulisciSchermo();
              printf("==============================\n");
              printf("\tRICERCA PER ID\n");
              printf("==============================\n");
              printf("Inserisci l'ID del cliente\n");
              scanf("%s",ID);
              is=hashSearch(h,ID);

              if(is==NULL){
                printf("\n==============================\n");
                printf("Cliente Insistente\n");
                printf("==============================\n");
                break;
              }
              stampaCliente(is);
              break;
            case '2':
              pulisciSchermo();
              printf("==============================\n");
              printf("\tRICERCA PER NOME\n");
              printf("==============================\n");
              printf("Inserisci il nome del cliente\n");
              scanf("%s",nome);
              if(ricercaGenerica(h,0,nome)==0){
                printf("==============================\n");
                printf("Cliente Insistente\n");
                printf("==============================\n");
                break;
              }
              break;
            case '3':
              pulisciSchermo();
              printf("==============================\n");
              printf("\tRICERCA PER COGNOME\n");
              printf("==============================\n");
              printf("Inserisci il cognome del cliente\n");
              scanf("%s",cognome);
              if(ricercaGenerica(h,1,cognome)==0){
                printf("==============================\n");
                printf("Cliente Insistente\n");
                printf("==============================\n");
                break;
              }
              break;
            case '4':
              pulisciSchermo();
              printf("==============================\n");
              printf("  RICERCA DURATA ABBONAMENTO\n");
              printf("==============================\n");
              printf("Inserisci il numero di mesi\n");
              scanf("%d",&durata);
              if(ricercaPerDurata(h,durata)==0){
                printf("==============================\n");
                printf("Cliente Insistente\n");
                printf("==============================\n");
                break;
              }
              break;
          }
        }while(selA>'5'||selA<'1');

        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
      case '4':
        char selElenco;
        do{
          getchar();
          pulisciSchermo();
          printf("==============================\n");
          printf("\tELENCO CLIENTI\n");
          printf("==============================\n");
          printf("Come vuoi visualizzare l'elenco?\n");
          printf("1. Visione Essenziale (ID, Cognome, Nome)\n");
          printf("2. Visione Estesa (Tutti i Dati)\n");
          printf("3. Esci\n");
          scanf("%c",&selElenco);
          switch(selElenco){
            case '1':
              pulisciSchermo();
              printf("==============================\n");
              printf("\tELENCO CLIENTI\n");
              printf("==============================\n");
              stampaHashMinima(h);

              printf("Premere invio per tornare indietro\n");
              getchar();
              break;
            case '2':
              pulisciSchermo();
              stampaHash(h);
              printf("Premere invio per tornare indietro\n");
              getchar();
              break;
          }
        }while(selElenco>'3'||selElenco<'1');
        break;
      case '5':
        pulisciSchermo();
        printf("==============================\n");
        printf("\tCANCELLA CLIENTE\n");
        printf("==============================\n");
        printf("Inserisci l'ID del Cliente da cancellare\n");
        stampaHashMinima(h);
        scanf("%s",ID);
        is=hashDelete(h,ID);
        if(is==NULL){
          printf("==============================\n");
          printf("CLIENTE INESISTENTE\n");
          printf("==============================\n");
        }
        printf("==============================\n");
        printf("\tCLIENTE CANCELLATO \n");
        printf("==============================\n");
        scriviFileClienti(h);
        printf("\nPremere invio per tornare indietro\n");
        getchar();
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

void menuCorso(list lCorsi) {
  //Dichiarazione delle variabili
  char selC;
  string nome = malloc(sizeof(char) * 50);
  string IDCorso = malloc(sizeof(char) * 7);
  Data dataLezione;
  int gg,mm,anno;
  int ora,minuti;
  int durata;
  list result=newList();
  Corso c;
  if(nome==NULL || IDCorso==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

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

        printf("Inserisci il nome del corso:\n");
        scanf("%s",nome);
        printf("Inserisci la data del corso (GG/MM/AAAA):\n");;
        scanf("%d/%d/%d",&gg,&mm,&anno);
        printf("Inserisci l'orario del corso (HH:MM)\n");
        scanf("%d:%d",&ora,&minuti);


        strcpy(IDCorso, generaIDCorso());
        dataLezione=creaData(gg,mm,anno);
        c=creaCorso(IDCorso,nome,dataLezione,ora,minuti,0);
        if(c==NULL){
          pulisciSchermo();
          printf("==============================\n");
          printf("\tDATI NON VALIDI\n");
          printf("       CORSO NON SALVATO\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }
        printf("\n==============================\n");
        printf("\tCORSO AGGIUNTO\n");
        stampaCorso(c);
        if(insertList(lCorsi,0,c)==0){
          printf("Errore nell'inserimento");
        }
        scriviFileCorso(lCorsi);

        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
      }

      case '2':
        char selRicerca;
        do{
          pulisciSchermo();
          printf("==============================\n");
          printf("\tCERCA CORSO\n");
          printf("==============================\n");
          printf("1. ID\n");
          printf("2. Nome\n");
          printf("3. Lezione Imminente\n");//da implementare
          printf("4. Data\n");
          printf("5. Orario\n");
          printf("6. Esci\n");
          scanf("%c", &selRicerca);
          switch(selRicerca) {
            case '1':
              pulisciSchermo();
              printf("==============================\n");
              printf("\tRICERCA PER ID\n");
              printf("==============================\n");
              printf("Inserisci l'ID del corso:\n");
              scanf("%s", IDCorso);
				result=ricercaGenericaLista(lCorsi,0,IDCorso);
              if(isEmpty(result)==1){
                printf("==============================\n");
                printf("\tCORSO INESISTENTE\n");
                printf("==============================\n");
                printf("\nPremere invio per tornare indietro\n");
                getchar();
				break;
              }
			  stampaLista(result);
			  printf("\nPremere invio per tornare indietro\n");
			  getchar();
              break;
            case '2':
              pulisciSchermo();
              getchar();
              printf("==============================\n");
              printf("\tRICERCA PER NOME\n");
              printf("==============================\n");
              printf("Inserisci il Nome del corso:\n");
			  scanf("%s", nome);
			  result=ricercaGenericaLista(lCorsi,1,nome);
              if(isEmpty(result)==1){
                printf("==============================\n");
                printf("\tCORSO INESISTENTE\n");
                printf("==============================\n");
                printf("\nPremere invio per tornare indietro\n");
                getchar();
				break;
              }
			  stampaLista(result);
              printf("\nPremere invio per tornare indietro\n");
              getchar();

              break;
            case '3'://da implementare
              pulisciSchermo();
              printf("==============================\n");
              printf("\tLEZIONE IMMINENTE\n");
              printf("==============================\n");


              printf("\nPremere invio per tornare indietro\n");
              getchar();
              break;
            case '4':
              int gg,mm,anno;
              pulisciSchermo();
              printf("==============================\n");
              printf("\tRICERCA PER DATA\n");
              printf("==============================\n");
              printf("Inserisci la data del corso (GG/MM/AAAA):\n");
              scanf("%d/%d/%d",&gg,&mm,&anno);
              Data cerca=creaData(gg,mm,anno);
			  result=ricercaData(lCorsi,cerca);
              if(isEmpty(result)==1){
                printf("==============================\n");
                printf("\tCORSO INESISTENTE\n");
                printf("==============================\n");
                printf("\nPremere invio per tornare indietro\n");
                getchar();
				break;
              }
			  stampaLista(result);
              printf("\nPremere invio per tornare indietro\n");
              getchar();
              break;
            case '5':
              pulisciSchermo();
              printf("==============================\n");
              printf(" RICERCA PER ORARIO LEZIONI\n");
              printf("==============================\n");
              printf("Inserisci l'orario del corso (HH:MM):\n");
              scanf("%d:%d",&ora,&minuti);
			  result=ricercaOrario(lCorsi,ora,minuti);
              if(isEmpty(result)==1){
                printf("==============================\n");
                printf("\tCORSO INESISTENTE\n");
                printf("==============================\n");
                printf("\nPremere invio per tornare indietro\n");
                getchar();
				break;
              }
			  stampaLista(result);
              printf("\nPremere invio per tornare indietro\n");
              getchar();
              break;
          }
        }while(selRicerca>'6'||selRicerca<'1');
        break;

      case '3':
        pulisciSchermo();
		printf("==============================\n");
  		printf("\tELENCO CORSI\n");
  		printf("==============================\n");
        stampaLista(lCorsi);

        printf("Premere invio per tornare indietro\n");
        getchar();
        break;

      case '4'://DA IMPLEMENTARE
        pulisciSchermo();
        printf("==============================\n");
        printf("\tELIMINA CORSO\n");
        printf("==============================\n");
        string IDDaEliminare = malloc(sizeof(char) * 7);
        if(IDDaEliminare == NULL){
          printf("Errore allocazione memoria\n");
          exit(1);
        }
        printf("Inserisci l'ID del corso da eliminare:\n");
        scanf("%s", IDDaEliminare);
       // listaCorsi = eliminaCorso(listaCorsi, IDDaEliminare); // funzione da implementare
        printf("Premere invio per tornare indietro\n");
        getchar();
        break;

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
  listP lPrenotati=newListPrenotati();
  caricaFileClienti(hClienti);
  caricaFileCorso(listaCorsi);

  //listaCorsi=reverseList(listaCorsi);

  //stampaLista(listaCorsi);

  char selettore;
  do{
    pulisciSchermo();
    printf("Gestore Palestra\n");
    printf("1. Gestione Abbonamenti\n");
    printf("2. Gestione Prenotazione\n");
    printf("3. Gestione Corso\n");
    printf("4. Esci\n");
    scanf("%c",&selettore);

    switch(selettore){
      case '1':
        menuAbbonamento(hClienti);
        getchar();
        break;
      case '2':
        menuPrenotazione(listaCorsi,hClienti,lPrenotati);
        getchar();
        break;
      case '3':
		menuCorso(listaCorsi);
		getchar();
		break;
    }
    if(selettore!='1'&&selettore!='2'&&selettore!='3'&&selettore!='4'){
      printf("Scelta non valida \n");
    }
  }while(selettore!='4');
  scriviFileClienti(hClienti);
  scriviFileCorso(listaCorsi);
}