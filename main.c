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
#include "test.h"

/*
 * Funzione: menuPrenotazione
 * -----------------------------------
 * Gestisce il menu principale per le operazioni sulle prenotazioni.
 *
 * Parametri:
 *   lCorsi: lista dei corsi disponibili
 *   hClienti: hashtable dei clienti registrati
 *   lPrenotati: lista delle prenotazioni attive
 *
 * Pre-condizione:
 *   Tutte le strutture dati devono essere inizializzate correttamente.
 *
 * Post-condizione:
 *   Le operazioni selezionate dall'utente vengono eseguite e i file
 *   vengono aggiornati quando necessario.
 *
 * Come funziona:
 * - Presenta un menu con 5 opzioni (prenota, ricerca, elenco, elimina, esci)
 * - Per ogni operazione, valida i dati di input e verifica le pre-condizioni
 * - Gestisce gli errori e fornisce feedback appropriato all'utente
 * - Mantiene sincronizzati i file di persistenza dopo ogni modifica
 */
void menuPrenotazione(list lCorsi,hashtable hClienti,listP lPrenotati){
  char selP;
  Prenotazione pre;
  list result=newList();
  listP resultP=newListPrenotati();
  Iscritto i;
  string IDCliente=malloc(sizeof(char)*7);
  string IDCorso=malloc(sizeof(char)*7);
  string IDPrenotazione=malloc(sizeof(char)*7);
  string IDCancellare=malloc(sizeof(char)*7);
  Data dataPrenotazione;
  int gg,mm,anno;
  if(IDCliente==NULL||IDCorso==NULL||IDPrenotazione==NULL||IDCancellare==NULL){
    printf("Errore apertura file\n");
    return;
  }
  do{
    getchar();
    pulisciSchermo();
    printf("==============================\n");
    printf("     GESTORE PRENOTAZIONI\n");
    printf("==============================\n");
    printf("1. Prenota Corso\n");
    printf("2. Ricerca Prenotazione\n");
    printf("3. Elenco Prenotazione\n");
    printf("4. Elimina Prenotazione\n");
    printf("5. Torna al Menu'\n");
    scanf("%c",&selP);

    switch(selP){
      case '1': //da aggiungere l'incremento dei posti occupati del corso
        pulisciSchermo();
		    getchar();
        printf("==============================\n");
        printf("    AGGIUNGI PRENOTAZIONE\n");
        printf("==============================\n");
        printf("\nInserisci l'ID del Cliente\n");
		    stampaHashMinima(hClienti);
        scanf("%s",IDCliente);
		    i=hashSearch(hClienti,IDCliente);
        if(i==NULL){
          pulisciSchermo();
          printf("==============================\n");
          printf("     CLIENTE NON TROVATO\n");
          printf("==============================\n");
		      printf("\nPremere invio per tornare indietro\n");
          getchar();
		      break;
        }
        if(controlloAbbonamento(i)==1){
          pulisciSchermo();
          printf("==============================\n");
          printf("      ABBONAMENTO SCADUTO\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }
        pulisciSchermo();
        printf("==============================\n");
        printf("           CLIENTE\n");
        stampaCliente(i);
        printf("==============================\n");
        getchar();
        printf("\nInserisci l'ID del Corso\n");
        stampaListaEssenziale(lCorsi);
        scanf("%s",IDCorso);
		    result=ricercaGenericaLista(lCorsi,0,IDCorso);
        if(isEmpty(result)==1){
		      pulisciSchermo();
          printf("==============================\n");
          printf("      CORSO NON TROVATO\n");
          printf("==============================\n");
		      printf("\nPremere invio per tornare indietro\n");
          getchar();
		      break;
        }
        getchar();
        printf("\nPremere invio per continuare\n");
        getchar();
        if(confrontaData(getDataCorso(getFirstCorso(result)),dataOggi())==-1){
          pulisciSchermo();
          printf("==============================\n");
          printf("    IMPOSSIBILE PRENOTARE\n");
          printf("  LEZIONE ANTECEDENTE AD OGGI\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          break;
        }
        strcpy(IDPrenotazione,generaIDPrenotazione());
        pre=creaPrenotazione(IDPrenotazione,IDCorso,IDCliente,dataOggi());

        if(insertListPrenotati(lPrenotati,0,pre)==0){
          printf("Errore nell'Inserimento\n");
		      break;
        }
        incrementaPartecipanti(getFirstCorso(result));

		    pulisciSchermo();
		    printf("==============================\n");
        printf("    PRENOTAZIONE AGGIUNTA\n");
		    printf("==============================\n");
		    stampaPrenotazione(pre);
        scriviFilePrenotazione(lPrenotati);
        scriviFileCorso(lCorsi);
        printf("\nPremere invio per tornare indietro\n");
        break;
      case '2':
        char selRicercaPrenotazione;
        do{
          getchar();
          pulisciSchermo();
          printf("==============================\n");
          printf("     RICERCA PRENOTAZIONI\n");
          printf("==============================\n");
          printf("Cosa vuoi Cercare?\n");
          printf("1. Prenotazioni di un Cliente\n");
          printf("2. Prenotati di un Corso\n");
          printf("3. Esci\n");
          scanf("%c",&selRicercaPrenotazione);

          switch(selRicercaPrenotazione){

            case '1':
              pulisciSchermo();
              getchar();
              printf("==============================\n");
              printf("  PRENOTAZIONI DI UN CLIENTE\n");
              printf("==============================\n");
              printf("Inserisci l'ID del Cliente\n");
              scanf("%s",IDCliente);
              //Controllo che il cliente sia presente nella lista e ne stampo i dettagli
              i=hashSearch(hClienti,IDCliente);
              if(i==NULL){
                pulisciSchermo();
                printf("==============================\n");
                printf("     CLIENTE NON TROVATO\n");
                printf("==============================\n");
                printf("\nPremere invio per tornare indietro\n");
                getchar();
                break;
              }
              //Controllo se l'abbonamento è valido per accedere all'elenco prenotazioni
              if(controlloAbbonamento(i)==1){
                pulisciSchermo();
                printf("==============================\n");
                printf("      ABBONAMENTO SCADUTO\n");
                printf("==============================\n");
                printf("\nPremere invio per tornare indietro\n");
                getchar();
                break;
              }
              stampaCliente(i);
              //Controllo se il cliente ha prenotazioni o meno
              resultP=ricercaListaPrenotati(lPrenotati,0,IDCliente);
              if(isEmptyPrenotazione(resultP)==1){
                pulisciSchermo();
                printf("==============================\n");
                printf("IL CLIENTE NON HA PRENOTAZIONI\n");
                printf("==============================\n");
                printf("\nPremere invio per tornare indietro\n");
                getchar();
                break;
              }
              printf("==============================\n");
              printf("     ELENCO PRENOTAZIONI\n");
              printf("==============================\n");
              stampaListaPrenotazioni(resultP);
              printf("\nPremere invio per tornare indietro\n");
              getchar();
              break;
            case '2':
              pulisciSchermo();
              getchar();
              printf("==============================\n");
              printf("    PRENOTATI DI UN CORSO\n");
              printf("==============================\n");
              printf("Inserisci l'ID del Corso\n");
              scanf("%s",IDCorso);
              //Controllo se il corso presenta prenotati o meno
              resultP=ricercaListaPrenotati(lPrenotati,1,IDCorso);
              if(isEmptyPrenotazione(resultP)==1){
                pulisciSchermo();
                printf("==============================\n");
                printf("  IL CORSO NON HA PRENOTATI\n");
                printf("==============================\n");
                printf("\nPremere invio per tornare indietro\n");
                getchar();
                break;
              }
              printf("==============================\n");
              printf("     ELENCO PRENOTAZIONI\n");
              printf("==============================\n");
              stampaListaPrenotazioni(resultP);
              printf("\nPremere invio per tornare indietro\n");
              getchar();
              break;
          }
        }while(selRicercaPrenotazione>'3'||selRicercaPrenotazione<'1');
        break;
      case '3':
        pulisciSchermo();
        printf("==============================\n");
        printf("     ELENCO PRENOTAZIONI\n");
        printf("==============================\n");
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

		    //Controllo che il cliente sia presente nella lista dei clienti
        i=hashSearch(hClienti,IDCliente);
        if(i==NULL){
          pulisciSchermo();
          printf("==============================\n");
          printf("     CLIENTE NON TROVATO\n");
		      printf("==============================\n");
		      printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }
        if(controlloAbbonamento(i)==1){
          pulisciSchermo();
          printf("==============================\n");
          printf("      ABBONAMENTO SCADUTO\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }
        //Controllo che il cliente abbia prenotazioni da cancellare
        resultP=ricercaListaPrenotati(lPrenotati,0,IDCliente);
        if(isEmptyPrenotazione(resultP)==1){
          pulisciSchermo();
          printf("==============================\n");
          printf("IL CLIENTE NON HA PRENOTAZIONI\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }
        //stampa più semplice e essenziale, da implementare
        //Stampo le prenotazioni del cliente e richiedo la prenotazione da cancellare
        printf("==============================\n");
        printf("     ELENCO PRENOTAZIONI\n");
        printf("==============================\n");
        stampaListaPrenotazioni(resultP);
        printf("Inserire l'ID della Prenotazione da Cancellare\n");
        scanf("%s",IDCancellare);
        //ricerco la prenotazione per decrementare il numero di partecipanti alla lezione
        resultP=ricercaListaPrenotati(lPrenotati,2,IDCancellare);
        if(isEmptyPrenotazione(resultP)==1){
          pulisciSchermo();
          printf("==============================\n");
          printf("   PRENOTAZIONE INESISTENTE\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }

        if(cancellaPrenotazione(lPrenotati,IDCancellare,IDCliente)==0){
          pulisciSchermo();
          printf("==============================\n");
          printf(" PRENOTAZIONE NON CANCELLATA\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }
        result=ricercaGenericaLista(lCorsi,0,getIDCorsoPrenotazione(getFirstPrenotazione(resultP)));
        decrementaPartecipanti(getFirstCorso(result));
        pulisciSchermo();
        printf("==============================\n");
        printf("   PRENOTAZIONE CANCELLATA\n");
        printf("==============================\n");
        scriviFilePrenotazione(lPrenotati);
        scriviFileCorso(lCorsi);
        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;

      default:
        printf("Scelta non valida \n");
        break;
    }
    if(selP=='5')
      break;
  }while(selP>'5'||selP<'1');
}

/*
 * Funzione: menuCliente
 * -----------------------------------
 * Gestisce tutte le operazioni relative ai clienti della palestra.
 *
 * Parametri:
 *   h: hashtable dei clienti
 *   lPrenotati: lista delle prenotazioni (per gestire cancellazioni correlate)
 *   lCorsi: lista dei corsi (per riferimenti incrociati)
 *
 * Pre-condizione:
 *   Tutte le strutture dati devono essere inizializzate.
 *
 * Post-condizione:
 *   I file vengono aggiornati dopo ogni operazione di modifica.
 *
 * Operazioni disponibili:
 * - Creazione nuovo abbonamento
 * - Rinnovo abbonamento esistente
 * - Ricerca clienti (per ID, nome, cognome, durata)
 * - Visualizzazione elenco clienti
 * - Eliminazione cliente (con cancellazione prenotazioni correlate)
 */
void menuCliente(hashtable h,listP lPrenotati,list lCorsi){

  int durata,gg,mm,anno;
  int trovato;
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
    printf("==============================\n");
    printf("       GESTORE CLIENTI\n");
    printf("==============================\n");
    printf("1. Crea Abbonamento\n");
    printf("2. Rinnova Abbonamento\n");
    printf("3. Ricerca Abbonamento\n");
    printf("4. Elenco Clienti\n");
    printf("5. Elimina Abbonamento\n");
    printf("6. Torna al Menu'\n");
    scanf("%c",&selA);

    switch(selA){
      case '1':
        pulisciSchermo();
        printf("==============================\n");
        printf("       AGGIUNGI CLIENTE\n");
        printf("==============================\n");
        printf("Inserisci nome\n");
        scanf("%s",nome);
        printf("Inserisci cognome\n");
        scanf("%s",cognome);

        printf("Inserisci la data d'iscrizione(GG/MM/AAAA):\n");
        scanf("%d/%d/%d",&gg,&mm,&anno);
        dataIscrizione=creaData(gg,mm,anno);
        printf("Inserisci la durata dell'abbonamento in mesi (ES. 1, 3, 6, ...)\n");
        do{
          scanf("%d",&durata);
          if(durata<=0)
            printf("Durata inferiore a 1.\nRiprova l'inserimento\n");
        }while(durata<=0);
        /*
        Genero l'ID del Cliente e controllo
        che l'inserimento sia andato a buon fine
        */
        strcpy(ID,generaIDCliente());
        is=CreaIscritto(nome,cognome,dataIscrizione,durata,ID);
        if(insertHash(h,is)==0){
          pulisciSchermo();
          printf("==============================\n");
          printf("   ERRORE NELL'INSERIMENTO\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }
        printf("\n==============================\n");
        printf("       CLIENTE AGGIUNTO\n");
        stampaCliente(is);
        //Ad ogni inserimento scrivo il nuovo iscritto nel file
        scriviFileClienti(h);
        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
      case '2':
        pulisciSchermo();
        printf("==============================\n");
        printf("     RINNOVO ABBONAMENTO\n");
        printf("==============================\n");

        int nuovaDurata;
        printf("Inserisci l'ID del Cliente\n");
        stampaHashMinima(h);
        scanf("%s",ID);
        //Controllo se il cliente esiste nella lista
        is=hashSearch(h,ID);
        if(is==NULL){
          pulisciSchermo();
          printf("==============================\n");
          printf("     CLIENTE INESISTENTE\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }

        do{//Ciclo affinchè non inserisce una durata valida
          printf("Di quanti mesi vuoi espandere l'abbonamento?\n");
          scanf("%d",&nuovaDurata);
        }while(nuovaDurata<0);

        rinnovaAbbonamento(is,nuovaDurata);
        printf("==============================\n");
        printf("      CLIENTE AGGIORNATO\n");
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
          printf("     RICERCA ABBONAMENTO\n");
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
              printf("       RICERCA PER ID\n");
              printf("==============================\n");
              printf("Inserisci l'ID del cliente\n");
              scanf("%s",ID);
              printf("\n");
              //Controllo se il cliente esiste nella lista
              is=hashSearch(h,ID);
              if(is==NULL){
                pulisciSchermo();
                printf("==============================\n");
                printf("     CLIENTE INESISTENTE\n");
                printf("==============================\n");
                break;
              }
              if(controlloAbbonamento(is)==1){
                pulisciSchermo();
                printf("==============================\n");
                printf("      ABBONAMENTO SCADUTO\n");
                printf("==============================\n");
                break;
              }
              stampaCliente(is);
              break;
            case '2':
              pulisciSchermo();
              printf("==============================\n");
              printf("       RICERCA PER NOME\n");
              printf("==============================\n");
              printf("Inserisci il nome del cliente\n");
              scanf("%s",nome);
              /*Controllo se il cliente esiste nella lista
              * se esiste ne stampo i dettagli.
              * La ricerca per 0 è per il nome del Cliente
              */
              printf("\n");
              trovato=ricercaGenerica(h,0,nome);
              if(trovato==0){
                pulisciSchermo();
                printf("==============================\n");
                printf("     CLIENTE INESISTENTE\n");
                printf("==============================\n");
                break;
              }
              if(trovato==-1){
                pulisciSchermo();
                printf("==============================\n");
                printf("      ABBONAMENTO SCADUTO\n");
                printf("==============================\n");
                break;
              }
              break;
            case '3':
              pulisciSchermo();
              printf("==============================\n");
              printf("     RICERCA PER COGNOME\n");
              printf("==============================\n");
              printf("Inserisci il cognome del cliente\n");
              scanf("%s",cognome);
              /*Controllo se il cliente esiste nella lista
              * se esiste ne stampo i dettagli.
              * La ricerca per 1 è per il cognome del Cliente
              */
              printf("\n");
              trovato=ricercaGenerica(h,1,cognome);
              if(trovato==0){
                pulisciSchermo();
                printf("==============================\n");
                printf("     CLIENTE INESISTENTE\n");
                printf("==============================\n");
                break;
              }
              if(trovato==-1){
                pulisciSchermo();
                printf("==============================\n");
                printf("      ABBONAMENTO SCADUTO\n");
                printf("==============================\n");
                break;
              }
              break;
            case '4':
              string strDurata=malloc(sizeof(char)*5);
              pulisciSchermo();
              printf("==============================\n");
              printf("  RICERCA DURATA ABBONAMENTO\n");
              printf("==============================\n");
              printf("Inserisci il numero di mesi\n");
              scanf("%s",strDurata);
              printf("\n");
              if(ricercaGenerica(h,2,strDurata)==0){
                pulisciSchermo();
                printf("==============================\n");
                printf("     CLIENTE INESISTENTE\n");
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
          printf("        ELENCO CLIENTI\n");
          printf("==============================\n");
          printf("Come vuoi visualizzare l'elenco?\n");
          printf("1. Visione Compatta (ID, Cognome, Nome)\n");
          printf("2. Visione Estesa (Tutti i Dati)\n");
          printf("3. Esci\n");
          scanf("%c",&selElenco);
          switch(selElenco){
            case '1':
              pulisciSchermo();
              printf("==============================\n");
              printf("        ELENCO CLIENTI\n");
              printf("==============================\n");
              stampaHashMinima(h);

              printf("Premere invio per tornare indietro\n");
              getchar();
              break;
            case '2':
              pulisciSchermo();
              printf("==============================\n");
              printf("        ELENCO CLIENTI\n");
              printf("==============================\n");
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
        printf("       CANCELLA CLIENTE\n");
        printf("==============================\n");
        //Nel richiedere l'ID stampo tutti i clienti in versione sintetica
        printf("Inserisci l'ID del Cliente da cancellare\n");
        stampaHashMinima(h);
        scanf("%s",ID);
        //ricerco l'iscritto da cancellare, ritornandolo e liberandolo nel main
        is=hashDelete(h,ID);
        if(is==NULL){
          pulisciSchermo();
          printf("==============================\n");
          printf("     CLIENTE INESISTENTE\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }
        //Funzione per liberare lo spazio occupato da iscritto

        printf("==============================\n");
        printf("      CLIENTE CANCELLATO\n");
        printf("==============================\n");
        printf("N Prenotazioni Cancellate: %d\n",cancellaPrenotazioneDi(lPrenotati,0,getID(is)));

        eliminaIscritto(is);
        //Anche per la cancellazione la scrittura avviene subito dopo l'operazione
        scriviFileClienti(h);
        scriviFilePrenotazione(lPrenotati);
        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
    }
    if(selA=='6')
      break;
  }while(selA>'6'||selA<'1');
}

/*
 * Funzione: menuCorso
 * -----------------------------------
 * Gestisce tutte le operazioni relative ai corsi/lezioni della palestra.
 *
 * Parametri:
 *   lCorsi: lista dei corsi disponibili
 *   lPrenotati: lista prenotazioni (per gestire cancellazioni correlate)
 *
 * Pre-condizione:
 *   Le strutture dati devono essere inizializzate.
 *
 * Post-condizione:
 *   I file vengono aggiornati dopo ogni modifica.
 *
 * Operazioni disponibili:
 * - Aggiunta nuovo corso
 * - Ricerca corsi (per ID, nome, data, orario)
 * - Visualizzazione elenco corsi
 * - Eliminazione corso (con cancellazione prenotazioni correlate)
 */
void menuCorso(list lCorsi,listP lPrenotati) {
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
    printf("==============================\n");
    printf("        GESTORE CORSI\n");
    printf("==============================\n");
    printf("1. Aggiungi Corso\n");
    printf("2. Ricerca Corso\n");
    printf("3. Elenco Corsi\n");
    printf("4. Elimina Corso\n");
    printf("5. Torna al Menu'\n");
    scanf("%c", &selC);

    switch(selC) {
      case '1': {
        pulisciSchermo();
        printf("==============================\n");
        printf("        AGGIUNGI CORSO\n");
        printf("==============================\n");

        printf("Inserisci il nome del corso:\n");
        scanf("%s",nome);
        do{
          printf("Inserisci la data del corso (GG/MM/AAAA):\n");;
          scanf("%d/%d/%d",&gg,&mm,&anno);
          dataLezione=creaData(gg,mm,anno);
          //mi assicuro che la data della lezione sia successiva alla data odierna
          if(confrontaData(dataLezione,dataOggi())<=0)
            printf("Data antecedente ad OGGI\n");
        }while(confrontaData(dataLezione,dataOggi())<=0);

        printf("Inserisci l'orario del corso (HH:MM)\n");
        scanf("%d:%d",&ora,&minuti);
        strcpy(IDCorso, generaIDCorso());

        c=creaCorso(IDCorso,nome,dataLezione,ora,minuti,0);
        if(c==NULL){
          pulisciSchermo();
          printf("==============================\n");
          printf("    ERRORE NELLA CREAZIONE\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
        }
        if(insertList(lCorsi,0,c)==0){
          pulisciSchermo();
          printf("==============================\n");
          printf("   ERRORE NELL'INSERIMENTO\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
        }
        printf("\n==============================\n");
        printf("        CORSO AGGIUNTO\n");
        stampaCorso(c);
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
          printf("         CERCA CORSO\n");
          printf("==============================\n");
          printf("1. ID\n");
          printf("2. Nome\n");
          printf("3. Data\n");
          printf("4. Orario\n");
          printf("5. Esci\n");
          scanf("%c", &selRicerca);
          switch(selRicerca) {
            case '1':
              pulisciSchermo();
              printf("==============================\n");
              printf("        RICERCA PER ID\n");
              printf("==============================\n");
              printf("Inserisci l'ID del corso:\n");
              scanf("%s", IDCorso);
              /*
               *La ricerca del corso a differenza di quella per iscritto
               *ritorna una lista, in quanto in altri punti del codice
               *ci occorre lavorare sui risultati ottenuti
               */
			        result=ricercaGenericaLista(lCorsi,0,IDCorso);
              if(isEmpty(result)==1){
                printf("==============================\n");
                printf("      CORSO INESISTENTE\n");
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
            case '3':
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
            case '4':
              pulisciSchermo();
              printf("==============================\n");
              printf(" RICERCA PER ORARIO LEZIONI\n");
              printf("==============================\n");
              printf("Inserisci l'orario del corso (HH:MM):\n");
              scanf("%d:%d",&ora,&minuti);
			        result=ricercaOrario(lCorsi,ora,minuti);
              if(isEmpty(result)==1){
                printf("==============================\n");
                printf("      CORSO INESISTENTE\n");
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
        }while(selRicerca>'5'||selRicerca<'1');
        break;

      case '3':
        char selElencoCorsi;
        do{
          pulisciSchermo();
		      printf("==============================\n");
  		    printf("         ELENCO CORSI\n");
  		    printf("==============================\n");
          printf("1. Versione Compatta\n");
          printf("2. Versione Estesa\n");
          printf("3. Esci\n");
          scanf("%c",&selElencoCorsi);

          switch(selElencoCorsi){
            case '1':
              pulisciSchermo();
              printf("==========================================\n");
              printf("              ELENCO CORSI\n");
              printf("==========================================\n");
              stampaListaEssenziale(lCorsi);
              printf("Premere invio per tornare indietro\n");
              getchar();
              break;
            case '2':
              pulisciSchermo();
              printf("==============================\n");
              printf("         ELENCO CORSI\n");
              printf("==============================\n");
              stampaLista(lCorsi);
              printf("Premere invio per tornare indietro\n");
              getchar();
              break;
          }
        }while(selElencoCorsi>'3'||selElencoCorsi<'1');
        break;

      case '4':
        pulisciSchermo();
        printf("==============================\n");
        printf("        ELIMINA CORSO\n");
        printf("==============================\n");
        printf("Inserisci l'ID del corso da eliminare:\n");
        printf("NB: Verranno cancellate tutte le prenotazioni associate al corso\n");
        stampaListaEssenziale(lCorsi);
        scanf("%s", IDCorso);
		    if(cancellaCorso(lCorsi, IDCorso)==0){
		      printf("==============================\n");
          printf("      CORSO INESISTENTE\n");
          printf("==============================\n");
          printf("\nPremere invio per tornare indietro\n");
          getchar();
          break;
		    }

        printf("==============================\n");
        printf("       CORSO CANCELLATO\n");
        printf("==============================\n");
        printf("N Prenotazioni Cancellate: %d\n",cancellaPrenotazioneDi(lPrenotati,1,IDCorso));
        scriviFileCorso(lCorsi);
        scriviFilePrenotazione(lPrenotati);
        printf("\nPremere invio per tornare indietro\n");
        getchar();
        break;
      default:
        printf("Scelta non valida \n");
        break;
    }

    if(selC == '5')
      break;
  } while(selC < '1' || selC > '5');
}

/*
•  Funzione: report
•  -----------------------------------
•  Genera un report mensile sulle prenotazioni e sui corsi.
*
•  Parametri:
*   lCorsi: lista dei corsi disponibili.
*   hClienti: tabella hash contenente gli iscritti.
*   lPrenotati: lista delle prenotazioni effettuate.
*
•  Pre-condizione:
*   lCorsi ≠ NULL ∧ hClienti ≠ NULL ∧ lPrenotati ≠ NULL
*
•  Post-condizione:
*   Viene creato un file di report con:
*   - nome `report_<nome_mese>.txt`,
*   - numero di prenotazioni del mese corrente,
*   - corsi in evidenza del mese.
*
•  Come funziona:
•  - Ottiene il mese corrente dal sistema.
•  - Costruisce il nome del file di report in base al mese.
•  - Seleziona dalla lista prenotazioni e corsi solo quelli del mese.
•  - Calcola i tre corsi con più partecipanti ("lezioni in evidenza").
•  - Scrive le informazioni nel file.
•  - Chiude il file e attende conferma per tornare al menu.
•  - In caso di errori (allocazione o apertura file), stampa messaggio e termina.
*/
void report(list lCorsi,hashtable hClienti,listP lPrenotati){

  string mesi[]={"Gennaio","Febbraio","Marzo","Aprile","Maggio","Giugno","Luglio","Agosto","Settembre","Ottobre","Novembre","Dicembre"};
  string reportMese=malloc(sizeof(char)*20);
  if(reportMese==NULL){
    printf("Errore di allocazione\n");
    exit(0);
  }
  printf("==============================\n");
  printf("        Report Generato\n    Controllare la cartella\n");
  printf("==============================\n");
  list corsiDelMese=newList();
  list classifica=newList();
  listP prenotazioniDelMese=newListPrenotati();

  int meseReport=getMese(dataOggi());
  sprintf(reportMese,"report_%s.txt",mesi[meseReport-1]);

  FILE *f=fopen(reportMese,"w");
  if(f==NULL){
    printf("Errore nell'apertura del file\n");
    exit(0);
  }
  prenotazioniDelMese=ricercaMesePrenotazione(lPrenotati,meseReport);
  corsiDelMese=ricercaMese(lCorsi,meseReport);
  classifica=lezioniInEvidenza(corsiDelMese);
  fprintf(f,"Report di %s\n",mesi[meseReport-1]);
  fprintf(f,"\nNumero Prenotazioni del Mese: %d\n",getSize(prenotazioniDelMese));
  fprintf(f,"\nCorsi del Mese:\n");
  scriviLezioniInEvidenza(classifica,f);
  fclose(f);
  printf("Premere invio per tornare indietro\n");
  getchar();
}

int main(){

  hashtable hClienti=newHashtable(30);
  list listaCorsi=newList();
  listP lPrenotati=newListPrenotati();
  caricaFileClienti(hClienti);
  caricaFileCorso(listaCorsi);
  caricaFilePrenotazioni(lPrenotati);

  mainTest(hClienti,listaCorsi, lPrenotati);
  char selettore;
  do{
    pulisciSchermo();
    printf("==============================\n");
    printf("       Gestore Palestra\n");
    printf("==============================\n");
    printf("1. Gestione Clienti\n");
    printf("2. Gestione Corso\n");
    printf("3. Gestione Prenotazione\n");
    printf("4. Report Mensile\n");
    printf("5. Esci\n");
    scanf("%c",&selettore);

    switch(selettore){
      case '1':
        menuCliente(hClienti,lPrenotati,listaCorsi);
        getchar();
        break;
      case '2':
        menuCorso(listaCorsi,lPrenotati);
        getchar();
        break;
      case '3':
        menuPrenotazione(listaCorsi,hClienti,lPrenotati);
        getchar();
		    break;
      case '4':
        report(listaCorsi,hClienti,lPrenotati);
        getchar();
        break;
    }
    if(selettore!='1'&&selettore!='2'&&selettore!='3'&&selettore!='4'&&selettore!='5'){
      printf("Scelta non valida \n");
    }
  }while(selettore!='5');
  scriviFileClienti(hClienti);
  scriviFileCorso(listaCorsi);
  scriviFilePrenotazione(lPrenotati);
}