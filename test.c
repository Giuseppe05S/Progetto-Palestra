//
// Created by Giuseppe on 27/05/2025.
//

#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "liste.h"
#include "prenotazione.h"
#include "utils.h"
#include "listaPrenotazione.h"

int runTest(string nomeTest, int sel, hashtable hClienti,list lCorsi, listP lPrenotazioni);
int testValiditàAbbonamento(string input, string output, string oracle, hashtable hClienti);
int testCorrettaRegistrazionePrenotazione(string input,string output,string oracle, hashtable hClienti,list lCorsi);
int testReport(string input, string output, string oracle, hashtable hClienti);

/*
•  Funzione: mainTest
•  -----------------------------------
•  Funzione principale per l'esecuzione della test suite automatica.
*
•  Parametri:
*   hClienti: hashtable contenente tutti i clienti registrati.
*   lCorsi: lista dei corsi disponibili.
*   lPrenotazioni: lista delle prenotazioni effettuate.
*
•  Pre-condizione:
*   I file "testSuite.txt" deve esistere e contenere i test da eseguire.
*   Le strutture dati devono essere inizializzate correttamente.
*
•  Post-condizione:
*   Viene creato il file "testResult.txt" con i risultati dei test.
*   Tutti i test specificati nel file vengono eseguiti.
*
•  Come funziona:
•  - Apre il file testSuite.txt per leggere i test da eseguire.
•  - Per ogni test legge nome e tipologia.
•  - Esegue il test tramite runTest() e registra il risultato.
•  - Scrive "Pass" o "Fail" nel file di output per ogni test.
*/
void mainTest(hashtable hClienti,list lCorsi, listP lPrenotazioni){

	FILE* testSuite = fopen("testSuite.txt","r");
	FILE* testResult = fopen("testResult.txt","w");
	int result,sel;
	string nomeTest=malloc(sizeof(char)*50);
	if(testSuite == NULL || testResult == NULL){
		printf("Errore apertura file\n");
	}
	if(nomeTest == NULL){
		printf("Errore di Allocazione\n");
	}

	while(fscanf(testSuite,"%s %d",nomeTest, &sel) != EOF){
		result=runTest(nomeTest,sel,hClienti,lCorsi,lPrenotazioni);

		if(result==1)
			fprintf(testResult,"%s: Pass\n",nomeTest);
		else
			fprintf(testResult,"%s: Fail\n",nomeTest);
	}
	fclose(testSuite);
	fclose(testResult);
	free(nomeTest);
}
/*
•  Funzione: runTest
•  -----------------------------------
•  Esegue un singolo test basato sulla tipologia specificata.
*
•  Parametri:
*   nomeTest: nome del test da eseguire.
*   sel: selettore che identifica il tipo di test (1, 2, o 3).
*   hClienti: hashtable contenente i clienti.
*   lCorsi: lista dei corsi disponibili.
*   lPrenotazioni: lista delle prenotazioni.
*
•  Pre-condizione:
*   I file di input, output e oracle devono esistere per il test specificato.
*   sel deve essere un valore valido (1, 2, o 3).
*
•  Post-condizione:
*   Viene eseguito il test appropriato e restituito il risultato.
*
•  Come funziona:
•  - Costruisce i nomi dei file di input, output e oracle.
•  - Seleziona il test appropriato basato sul valore di sel.
•  - Esegue il test specifico e restituisce il risultato (1=Pass, 0=Fail).
*/
int runTest(string nomeTest, int sel, hashtable hClienti,list lCorsi, listP lPrenotazioni){

	string input=malloc(sizeof(char)*50);
	string output=malloc(sizeof(char)*50);
	string oracle=malloc(sizeof(char)*50);

	sprintf(input,"%s_Input.txt",nomeTest);
	sprintf(output,"%s_Output.txt",nomeTest);
	sprintf(oracle,"%s_Oracle.txt",nomeTest);
	int value;
	switch(sel){

		case 1:
			//TC1: Esiste sia il Cliente che il Corso
			//TC2: Esiste il Cliente ma non il Corso
			//TC3: Esiste il Corso ma non il Cliente
			//TC4: Non esistono nessuno dei due
			value=testCorrettaRegistrazionePrenotazione(input,output,oracle,hClienti,lCorsi);

			return value;
			break;
		case 2:
			//TC1: Abbonamento non scaduto
			//TC2: Abbonamento scaduto
			//TC3: Cliente inesistente
			value=testValiditàAbbonamento(input,output,oracle,hClienti);
			return value;
			break;
		case 3:
			value=testReport(input,output,oracle,hClienti);
			return value;
			break;
	}
}
/*
•  Funzione: testCorrettaRegistrazionePrenotazione
•  -----------------------------------
•  Testa la corretta registrazione di una prenotazione verificando l'esistenza di cliente e corso.
*
•  Parametri:
*   input: file contenente gli ID corso e cliente da testare.
*   output: file dove scrivere i risultati del test.
*   oracle: file contenente i risultati attesi.
*   hClienti: hashtable contenente i clienti registrati.
*   lCorsi: lista dei corsi disponibili.
*
•  Pre-condizione:
*   I file di input e oracle devono esistere e essere leggibili.
*   Le strutture dati devono essere inizializzate.
*
•  Post-condizione:
*   Viene creato il file di output con i risultati del test.
*   I risultati vengono confrontati con l'oracle.
*
•  Come funziona:
•  - Legge coppie di ID corso e cliente dal file di input.
•  - Verifica l'esistenza del corso nella lista e del cliente nella hashtable.
•  - Se entrambi esistono, crea una prenotazione di test.
•  - Scrive nel file di output l'ID corso, ID cliente e numero partecipanti.
•  - Confronta il file di output con l'oracle per determinare il successo.
*/
int testCorrettaRegistrazionePrenotazione(string input,string output,string oracle, hashtable hClienti,list lCorsi){
	FILE *fileInput,*fileOutput;
	fileInput = fopen(input,"r");
	fileOutput = fopen(output,"w");

	if(fileInput == NULL || fileOutput == NULL){
		printf("Errore apertura file\n");
		return 0;
	}
	string IDCliente=malloc(sizeof(char)*7);
	string IDCorso=malloc(sizeof(char)*7);
	if(IDCliente==NULL || IDCorso==NULL){
		printf("Errore nell'allocazione delle stringhe\n");
		fclose(fileInput);
		fclose(fileOutput);
		return 0;
	}
	list resultCorso;
	Prenotazione testPrenotazione;
	while(fscanf(fileInput,"%s %s",IDCorso,IDCliente)!=EOF){
		//controllo che il cliente e il corso esistano
		resultCorso=ricercaGenericaLista(lCorsi,0,IDCorso);
		if((hashSearch(hClienti,IDCliente)==NULL) || isEmpty(resultCorso)==1){
			fprintf(fileOutput,"Cliente o Corso inesistente");
			break;
		}else{
			testPrenotazione=creaPrenotazione(generaIDPrenotazione(),IDCorso,IDCliente,dataOggi());
			if(testPrenotazione==NULL){
				fprintf(fileOutput,"Errore nella creazione della prenotazione\n");
			}
			incrementaPartecipanti(getFirstCorso(resultCorso));
			fprintf(fileOutput,"%s %s %d",getIDCorsoPrenotazione(testPrenotazione),getIDClientePrenotazione(testPrenotazione),getNumPartecipantiCorso(getFirstCorso(resultCorso)));
			//decremento il numero di partecipanti in quanto la registrazione non viene registrata
			decrementaPartecipanti(getFirstCorso(resultCorso));
		}
	}
	fclose(fileInput);
	fclose(fileOutput);
	free(IDCorso);
	free(IDCliente);
	//int uguali=;
	if(confrontaFile(output,oracle))
		return 1;
	else
		return 0;
}
/*
•  Funzione: testValiditàAbbonamento
•  -----------------------------------
•  Testa la validità dell'abbonamento di un cliente verificando se è scaduto o meno.
*
•  Parametri:
*   input: file contenente gli ID dei clienti da verificare.
*   output: file dove scrivere i risultati del test.
*   oracle: file contenente i risultati attesi.
*   hClienti: hashtable contenente i clienti registrati.
*
•  Pre-condizione:
*   I file di input e oracle devono esistere e essere leggibili.
*   La hashtable dei clienti deve essere inizializzata.
*
•  Post-condizione:
*   Viene creato il file di output con lo stato dell'abbonamento.
*   I risultati vengono confrontati con l'oracle.
*
•  Come funziona:
•  - Legge gli ID dei clienti dal file di input.
•  - Cerca ogni cliente nella hashtable.
•  - Se il cliente esiste, controlla la validità del suo abbonamento.
•  - Scrive "Abbonamento Valido" o "Abbonamento Scaduto" nel file di output.
•  - Se il cliente non esiste, scrive "Cliente inesistente".
*/
int testValiditàAbbonamento(string input, string output, string oracle, hashtable hClienti){
	FILE *fileInput,*fileOutput;
	fileInput = fopen(input,"r");
	fileOutput = fopen(output,"w");

	if(fileInput == NULL || fileOutput == NULL){
		printf("Errore apertura file\n");
		return 0;
	}
	string IDCliente=malloc(sizeof(char)*7);
	if(IDCliente==NULL){
		printf("Errore nell'allocazione delle stringhe\n");
		fclose(fileInput);
		fclose(fileOutput);
		return 0;
	}
	Iscritto i;
	while(fscanf(fileInput,"%s",IDCliente)!=EOF){
		i=hashSearch(hClienti,IDCliente);
		if(i==NULL){
			fprintf(fileOutput,"Cliente inesistente");
			break;
		}else{
			if(controlloAbbonamento(i)==0)
				fprintf(fileOutput,"Abbonamento Valido");
			else
				fprintf(fileOutput,"Abbonamento Scaduto");
		}
	}
	fclose(fileInput);
	fclose(fileOutput);
	free(IDCliente);
	if(confrontaFile(output,oracle))
		return 1;
	else
		return 0;
}
/*
•  Funzione: testReport
•  -----------------------------------
•  Testa la generazione di un report mensile con prenotazioni e corsi in evidenza.
*
•  Parametri:
*   input: file contenente le prenotazioni di test da aggiungere.
*   output: file dove scrivere il report generato.
*   oracle: file contenente il report atteso.
*   hClienti: hashtable contenente i clienti registrati.
*
•  Pre-condizione:
*   I file di input e oracle devono esistere.
*   La hashtable dei clienti deve essere inizializzata.
*   I file dei corsi e prenotazioni devono essere disponibili.
*
•  Post-condizione:
*   Viene generato un report mensile completo nel file di output.
*   I risultati vengono confrontati con l'oracle.
*
•  Come funziona:
•  - Carica corsi e prenotazioni da file in nuove strutture dati.
•  - Legge le prenotazioni di test dal file di input.
•  - Verifica l'esistenza di cliente e corso per ogni prenotazione.
•  - Aggiunge le prenotazioni valide e incrementa i partecipanti.
•  - Genera un report con numero prenotazioni del mese e corsi in evidenza.
•  - Confronta il report generato con l'oracle.
*/
int testReport(string input, string output, string oracle, hashtable hClienti){

	FILE *fileInput,*fileOutput;
	fileInput = fopen(input,"r");
	fileOutput = fopen(output,"w");
	if(fileInput == NULL || fileOutput == NULL){
		printf("Errore apertura file\n");
		return 0;
	}

	string mesi[]={"Gennaio","Febbraio","Marzo","Aprile","Maggio","Giugno","Luglio","Agosto","Settembre","Ottobre","Novembre","Dicembre"};
	int meseR=getMese(dataOggi());
	/*Non ricevo la lista corsi e prenotazioni da parametri,
	* in quanto durante l'esecuzione della funzione, vado ad
	* alterale valori come il numero di partecipanti ad un corso,
	* per evitare quindi di rimodificare i valori, carico in una
	* nuova lista gli stessi corsi e le stesse prenotazioni, in
	* modo da usare i valori già presenti, in aggiunta a quelli
	* del test, che verranno poi scartati al termine del programma.
	*/
	list lCorsi=newList();
	listP PrenotatiTest=newListPrenotati();
	caricaFileCorso(lCorsi);
	caricaFilePrenotazioni(PrenotatiTest);

	string IDCliente=malloc(sizeof(char)*7);
	string IDCorso=malloc(sizeof(char)*7);
	if(IDCliente==NULL || IDCorso==NULL){
		printf("Errore nell'allocazione delle stringhe\n");
		fclose(fileInput);
		fclose(fileOutput);
		return 0;
	}
	list resultCorso=newList();
	list corsiDelMese=newList();
	list classifica=newList();

	Prenotazione newPrenotazione;
	//Carichiamo gli elementi nella nuova lista prenotazioni.
	while(fscanf(fileInput,"%s %s",IDCorso,IDCliente)!=EOF){
		resultCorso=ricercaGenericaLista(lCorsi,0,IDCorso);
		if((hashSearch(hClienti,IDCliente)==NULL) || isEmpty(resultCorso)==1){
			fprintf(fileOutput,"Cliente o Corso inesistente");
			return 0;
		}else{
			newPrenotazione=creaPrenotazione(generaIDPrenotazione(),IDCorso,IDCliente,dataOggi());
			if(newPrenotazione==NULL){
				fprintf(fileOutput,"Errore nella creazione della prenotazione\n");
				return 0;
			}
			if(insertListPrenotati(PrenotatiTest,0,newPrenotazione)==0){
				fprintf(fileOutput,"Errore nell'inserimento");
				return 0;
			}
			incrementaPartecipanti(getFirstCorso(resultCorso));
		}
	}


	corsiDelMese=ricercaMese(lCorsi,meseR);
	classifica=lezioniInEvidenza(corsiDelMese);
	fprintf(fileOutput,"Report di %s\n",mesi[meseR-1]);
	fprintf(fileOutput,"\nNumero Prenotazioni del Mese: %d\n",getSize(PrenotatiTest));
	fprintf(fileOutput,"\nCorsi del Mese:\n");
	scriviLezioniInEvidenza(classifica,fileOutput);
	fclose(fileOutput);
	fclose(fileInput);
	free(IDCliente);
	free(IDCorso);
	if(confrontaFile(output,oracle))
		return 1;
	else
		return 0;
}
/*
•  Funzione: confrontaFile
•  -----------------------------------
•  Confronta il contenuto di due file linea per linea per verificare se sono identici.
*
•  Parametri:
*   file1: percorso del primo file da confrontare.
*   file2: percorso del secondo file da confrontare.
*
•  Pre-condizione:
*   Entrambi i file devono esistere e essere leggibili.
*
•  Post-condizione:
*   Restituisce il risultato del confronto senza modificare i file.
*
•  Come funziona:
•  - Apre entrambi i file in modalità lettura.
•  - Legge una linea alla volta da entrambi i file.
•  - Confronta ogni coppia di linee usando strcmp().
•  - Se trova una differenza, interrompe il confronto.
•  - Chiude i file e libera la memoria allocata.
*/
int confrontaFile(string file1,string file2){
    FILE *f1=fopen(file1,"r");
    FILE *f2=fopen(file2,"r");
	if(f1==NULL||f2==NULL){
		printf("Errore apertura file\n");
		return 0;
	}
	string str1,str2;
	str1=malloc(sizeof(char)*256);
	str2=malloc(sizeof(char)*256);
	if(str1==NULL||str2==NULL){
		printf("Errore apertura file\n");
		return 0;
	}
	int uguali=1;
	while(fgets(str1,256,f1)!=NULL && fgets(str2,256,f2)!=NULL){
		if(strcmp(str1,str2)!=0){
            uguali=0;
			break;
        }
	}

	free(str1);
	free(str2);
    fclose(f1);
    fclose(f2);
	return uguali;
}