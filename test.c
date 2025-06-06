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
			break;
		case 3:

			break;
	}
}
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