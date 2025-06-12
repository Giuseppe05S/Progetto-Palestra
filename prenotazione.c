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

/*
•  Funzione: creaPrenotazione
•  -----------------------------------
•  Crea una nuova prenotazione nel sistema.
*
•  Parametri:
*   IDPrenotazione: identificativo univoco della prenotazione.
*   IDCorso: identificativo del corso da prenotare.
*   IDCliente: identificativo del cliente che effettua la prenotazione.
*   dataPrenotazione: data in cui viene effettuata la prenotazione.
*
•  Pre-condizione:
*   Tutti i parametri devono essere non NULL.
*   dataPrenotazione deve essere una data valida.
*
•  Post-condizione:
*   Viene creata una nuova prenotazione se tutti i parametri sono validi.
*   La memoria viene allocata dinamicamente per tutti i campi stringa.
*   La data viene copiata utilizzando copiaData().
*
•  Come funziona:
•  - Verifica la validità di tutti i parametri in input.
•  - Alloca memoria per la struttura prenotazione.
•  - Alloca memoria dinamicamente per tutti i campi stringa.
•  - Copia i dati utilizzando strcpy() per le stringhe e copiaData() per la data.
•  - Restituisce NULL in caso di errore di allocazione o parametri non validi.
*/
Prenotazione creaPrenotazione(string IDPrenotazione, string IDCorso, string IDCliente, Data dataPrenotazione){
  //Pre-condizioni
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
/*
•  Funzione: eliminaPrenotazione
•  -----------------------------------
•  Elimina una prenotazione liberando tutta la memoria associata.
*
•  Parametri:
*   pr: prenotazione da eliminare.
*
•  Pre-condizione:
*   pr può essere NULL (gestito dalla funzione).
*
•  Post-condizione:
*   Tutta la memoria associata alla prenotazione viene liberata.
*   La prenotazione non è più accessibile.
*
•  Come funziona:
•  - Verifica che la prenotazione non sia NULL.
•  - Libera la memoria di tutti i campi stringa.
•  - Libera la memoria della data.
•  - Libera la memoria della struttura principale.
*/
void eliminaPrenotazione(Prenotazione pr){
  //Pre-condizioni
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
/*
•  Funzione: getDataPrenotazione
•  -----------------------------------
•  Restituisce la data della prenotazione specificata.
*
•  Parametri:
*   pr: prenotazione da cui estrarre la data.
*
•  Pre-condizione:
*   pr deve essere una prenotazione valida (non NULL).
*
•  Post-condizione:
*   Restituisce la data associata alla prenotazione.
*   Il programma termina se pr è NULL.
*
•  Come funziona:
•  - Verifica che la prenotazione non sia NULL.
•  - Termina il programma con exit(1) se la prenotazione è NULL.
•  - Restituisce il campo dataPrenotazione.
*/
Data getDataPrenotazione(Prenotazione pr){
  //Pre-condizioni
  if(pr==NULL){
    printf("La prenotazione non esiste\n");
    exit(1);
  }
  return pr->dataPrenotazione;
}
/*
•  Funzione: getIDCorsoPrenotazione
•  -----------------------------------
•  Restituisce l'identificativo del corso associato alla prenotazione.
*
•  Parametri:
*   pr: prenotazione da cui estrarre l'ID corso.
*
•  Pre-condizione:
*   pr deve essere una prenotazione valida (non NULL).
*
•  Post-condizione:
*   Restituisce l'ID del corso associato alla prenotazione.
*   Il programma termina se pr è NULL.
*
•  Come funziona:
•  - Verifica che la prenotazione non sia NULL.
•  - Termina il programma con exit(1) se la prenotazione è NULL.
•  - Restituisce il campo IDCorso.
*/
string getIDCorsoPrenotazione(Prenotazione pr){
  //Pre-condizioni
  if(pr==NULL){
    printf("La prenotazione non esiste\n");
    exit(1);
  }
  return pr->IDCorso;
}
/*
•  Funzione: getIDClientePrenotazione
•  -----------------------------------
•  Restituisce l'identificativo del cliente associato alla prenotazione.
*
•  Parametri:
*   pr: prenotazione da cui estrarre l'ID cliente.
*
•  Pre-condizione:
*   pr deve essere una prenotazione valida (non NULL).
*
•  Post-condizione:
*   Restituisce l'ID del cliente associato alla prenotazione.
*   Il programma termina se pr è NULL.
*
•  Come funziona:
•  - Verifica che la prenotazione non sia NULL.
•  - Termina il programma con exit(1) se la prenotazione è NULL.
•  - Restituisce il campo IDCliente.
*/
string getIDClientePrenotazione(Prenotazione pr){
  //Pre-condizioni
  if(pr==NULL){
    printf("La prenotazione non esiste\n");
    exit(1);
  }
  return pr->IDCliente;
}
/*
•  Funzione: getIDPrenotazione
•  -----------------------------------
•  Restituisce l'identificativo univoco della prenotazione.
*
•  Parametri:
*   pr: prenotazione da cui estrarre l'ID.
*
•  Pre-condizione:
*   pr deve essere una prenotazione valida (non NULL).
*
•  Post-condizione:
*   Restituisce l'ID univoco della prenotazione.
*   Il programma termina se pr è NULL.
*
•  Come funziona:
•  - Verifica che la prenotazione non sia NULL.
•  - Termina il programma con exit(1) se la prenotazione è NULL.
•  - Restituisce il campo IDPrenotazione.
*/
string getIDPrenotazione(Prenotazione pr){
  //Pre-condizioni
  if(pr==NULL){
    printf("La prenotazione non esiste\n");
    exit(1);
  }
  return pr->IDPrenotazione;
}
/*
•  Funzione: stampaPrenotazione
•  -----------------------------------
•  Stampa su console tutti i dettagli della prenotazione in formato leggibile.
*
•  Parametri:
*   p: prenotazione da stampare.
*
•  Pre-condizione:
*   p può essere NULL (gestito dalla funzione).
*
•  Post-condizione:
*   I dettagli della prenotazione vengono stampati su console in formato strutturato.
*   Viene stampato un messaggio di errore se p è NULL.
*
•  Come funziona:
•  - Verifica che la prenotazione non sia NULL.
•  - Stampa una linea di separazione decorativa.
•  - Stampa ID prenotazione, ID corso, ID cliente.
•  - Stampa la data utilizzando la funzione stampaData().
•  - Gestisce il caso NULL stampando un messaggio di errore.
*/
void stampaPrenotazione(Prenotazione p){
  //Pre-condizioni
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
/*
•  Funzione: scriviPrenotazione
•  -----------------------------------
•  Scrive i dati della prenotazione su file in formato strutturato.
*
•  Parametri:
*   p: prenotazione da scrivere su file.
*   fp: puntatore al file di output aperto in scrittura.
*
•  Pre-condizione:
*   p deve essere una prenotazione valida.
*   fp deve essere un file aperto in modalità scrittura.
*
•  Post-condizione:
*   I dati della prenotazione vengono scritti su file nel formato:
*   "IDPrenotazione IDCorso IDCliente giorno mese anno".
*
•  Come funziona:
•  - Utilizza fprintf() per scrivere i dati su file.
•  - Scrive gli ID come stringhe separate da spazi.
•  - Estrae i componenti della data usando getGiorno(), getMese(), getAnno().
•  - Scrive i componenti della data come numeri interi.
•  - Termina la riga con un carattere di newline.
*/
void scriviPrenotazione(Prenotazione p,FILE *fp){
  //Pre-condizioni
  if(p==NULL){
    printf("La prenotazione non esiste\n");
    return;
  }
  fprintf(fp,"%s %s %s %d %d %d\n",p->IDPrenotazione,p->IDCorso,p->IDCliente,getGiorno(p->dataPrenotazione),getMese(p->dataPrenotazione),getAnno(p->dataPrenotazione));
}