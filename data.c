//
// Created by Giuseppe on 28/04/2025.
//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "data.h"

struct data{
  int giorno;
  int mese;
  int anno;
};

/*
•  Funzione: creaData
•  ------------------
•  Crea un nuovo oggetto Data con giorno, mese e anno specificati.
*
•  Parametri:
*   giorno: valore del giorno (1–31).
*   mese: valore del mese (1–12).
*   anno: valore dell'anno.
*
•  Pre-condizione:
*   giorno deve essere compreso tra 1 e 31;
*   mese deve essere compreso tra 1 e 12.
*
•  Post-condizione:
*   Viene restituito un nuovo oggetto Data allocato in memoria.
*   Se la data non è valida, viene richiesto un nuovo inserimento.
*
•  Come funziona:
•  - Valida i parametri di input tramite ciclo while.
•  - Se non validi, richiede nuovo inserimento da tastiera.
•  - Alloca memoria dinamicamente per la struttura.
•  - Inizializza i campi della struttura con i valori forniti.
*/

Data creaData(int giorno,int mese,int anno){
  //Precondizione
  //Controllo validità della data
  while(giorno<=0||giorno>31||mese<=0||mese>12){
    printf("Data non valida\n");
    printf("Inserisci la nuova data (GG/MM/AAAA):\n");
    scanf("%d/%d/%d",&giorno,&mese,&anno);
  }

  //Creazione e Allocazione Data
  Data data;
  data=malloc(sizeof(struct data));
  if(data==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  //Inizializzazione data
  data->giorno=giorno;
  data->mese=mese;
  data->anno=anno;
  return data;
}
/*
•  Funzione: calcoloDataScadenza
•  -----------------------------
•  Calcola la data di scadenza aggiungendo una durata in mesi alla data fornita.
*
•  Parametri:
*   data: data di partenza per il calcolo.
*   durata: numero di mesi da aggiungere alla data.
*
•  Pre-condizione:
*   data deve essere valida (non NULL);
*   durata deve essere maggiore di 0.
*
•  Post-condizione:
*   Viene restituita una nuova data con la scadenza calcolata.
*   Gestisce automaticamente il passaggio all'anno successivo se necessario.
*
•  Come funziona:
•  - Verifica le precondizioni sui parametri.
•  - Alloca memoria per la nuova data di scadenza.
•  - Copia giorno e anno dalla data originale.
•  - Aggiunge la durata ai mesi.
•  - Se i mesi superano 12, incrementa l'anno e sottrae 12 dai mesi.
*/

Data calcoloDataScadenza(Data data, int durata){
  //PreCondizione
  if(data==NULL||durata<=0){
    printf("Valori Errati\n");
    return NULL;
  }
  Data scadenza;
  scadenza=malloc(sizeof(struct data));
  if(scadenza==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }

  scadenza->giorno=data->giorno;
  scadenza->mese=data->mese+durata;
  scadenza->anno=data->anno;

  //Gestione rinnovo in anno successivo
  if(scadenza->mese>12){
    scadenza->mese-=12;
    scadenza->anno++;
  }
  return scadenza;
}
/*
•  Funzione: copiaData
•  -------------------
•  Crea una copia identica dell'oggetto Data fornito.
*
•  Parametri:
*   dataOriginale: data da copiare.
*
•  Pre-condizione:
*   dataOriginale deve essere valida (non NULL).
*
•  Post-condizione:
*   Viene restituita una nuova data identica all'originale.
*
•  Come funziona:
•  - Verifica che la data originale non sia NULL.
•  - Alloca memoria per la nuova data.
•  - Copia tutti i campi dalla data originale alla nuova.
*/
Data copiaData(Data dataOriginale){
  //Precondizione
  if(dataOriginale==NULL){
    printf("Valori inesistenti\n");
    return NULL;
  }
  Data d=malloc(sizeof(struct data));
  if(d==NULL){
    printf("Errore allocazione memoria\n");
    exit(1);
  }
  d->giorno=dataOriginale->giorno;
  d->mese=dataOriginale->mese;
  d->anno=dataOriginale->anno;
  return d;
}
/*
•  Funzione: stampaData
•  --------------------
•  Stampa la data nel formato GG/MM/AAAA.
*
•  Parametri:
*   data: data da stampare.
*
•  Pre-condizione:
*   data deve essere valida (non NULL).
*
•  Post-condizione:
*   La data viene stampata su stdout nel formato specificato.
*
•  Come funziona:
•  - Verifica che la data non sia NULL.
•  - Utilizza printf per stampare i campi nel formato richiesto.
*/
void stampaData(Data data){
  if(data==NULL){
    printf("Valori inesistenti\n");
    return;
  }
  printf("%d/%d/%d\n",data->giorno,data->mese,data->anno);
}

/*
•  Funzione: getGiorno
•  -------------------
•  Funzione accessor per ottenere il giorno della data.
*
•  Parametri:
*   data: data da cui estrarre il giorno.
*
•  Pre-condizione:
*   data deve essere valida (non NULL).
*
•  Post-condizione:
*   Viene restituito il valore del giorno.
*
•  Come funziona:
•  - Verifica che la data non sia NULL.
•  - Restituisce direttamente il campo giorno della struttura.
*/
int getGiorno(Data data){
  if(data==NULL){
    printf("Valori inesistenti\n");
    return -1;
  }
  return data->giorno;
}

/*
•  Funzione: getMese
•  -----------------
•  Funzione accessor per ottenere il mese della data.
*
•  Parametri:
*   data: data da cui estrarre il mese.
*
•  Pre-condizione:
*   data deve essere valida (non NULL).
*
•  Post-condizione:
*   Viene restituito il valore del mese.
*
•  Come funziona:
•  - Verifica che la data non sia NULL.
•  - Restituisce direttamente il campo mese della struttura.
*/
int getMese(Data data){
  if(data==NULL){
    printf("Valori inesistenti\n");
    return -1;
  }
  return data->mese;
}

/*
•  Funzione: getAnno
•  -----------------
•  Funzione accessor per ottenere l'anno della data.
*
•  Parametri:
*   data: data da cui estrarre l'anno.
*
•  Pre-condizione:
*   data deve essere valida (non NULL).
*
•  Post-condizione:
*   Viene restituito il valore dell'anno.
*
•  Come funziona:
•  - Verifica che la data non sia NULL.
•  - Restituisce direttamente il campo anno della struttura.
*/
int getAnno(Data data){
  if(data==NULL){
    printf("Valori inesistenti\n");
    return -1;
  }
  return data->anno;
}
/*
•  Funzione: confrontaData
•  -----------------------
•  Confronta due date e restituisce il risultato del confronto.
*
•  Parametri:
*   d1: prima data da confrontare.
*   d2: seconda data da confrontare.
*
•  Pre-condizione:
*   Entrambe le date devono essere valide (non NULL).
*
•  Post-condizione:
*   Viene restituito il risultato del confronto cronologico.
*
•  Come funziona:
•  - Verifica che entrambe le date non siano NULL (altrimenti termina).
•  - Confronta prima gli anni: se diversi, restituisce il risultato.
•  - Se anni uguali, confronta i mesi: se diversi, restituisce il risultato.
•  - Se mesi uguali, confronta i giorni e restituisce il risultato.
•  - Se tutti i campi sono uguali, restituisce 0.
*/
int confrontaData(Data d1, Data d2){// -1 se d1 < d2, 0 se d1 == d2, 1 se d1 > d2
  if(d1==NULL||d2==NULL){
    printf("Valori inesistenti\n");
    exit(1);
  }
  if(d1->anno > d2->anno)
    return 1;
  if(d1->anno < d2->anno)
    return -1;

  // Anno uguale, confronto i mesi
  if(d1->mese > d2->mese)
    return 1;
  if(d1->mese < d2->mese)
    return -1;

  // Mese uguale, confronto i giorni
  if(d1->giorno > d2->giorno)
    return 1;
  if(d1->giorno < d2->giorno)
    return -1;

  // Tutti uguali
  return 0;
}
/*
•  Funzione: dataOggi
•  ------------------
•  Crea un oggetto Data con la data corrente del sistema.
*
•  Parametri:
*   Nessuno.
*
•  Pre-condizione:
*   Nessuna.
*
•  Post-condizione:
*   Viene restituita la data corrente del sistema.
*
•  Come funziona:
•  - Chiama time(NULL) per ottenere il timestamp corrente.
•  - Usa localtime() per convertire in struttura tm locale.
•  - Estrae giorno (tm_mday), mese (tm_mon + 1), anno (tm_year + 1900).
•  - Chiama creaData() con i valori estratti.
*/
Data dataOggi(){
  time_t t = time(NULL);            // Ottieni tempo corrente
  //la struttura struct tm e' presente nella libreria <time.h>, così come la funzione localtime
  struct tm *tm_info = localtime(&t);  // Converti in tempo locale

  int giorno = tm_info->tm_mday;
  int mese = tm_info->tm_mon + 1;     // tm_mon parte da 0 (gennaio)
  int anno = tm_info->tm_year + 1900; // tm_year parte da 1900

  return creaData(giorno, mese, anno);
}