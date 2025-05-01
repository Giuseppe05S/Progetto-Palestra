//
// Created by Giuseppe on 28/04/2025.
//
#include <stdio.h>
#include <stdlib.h>
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