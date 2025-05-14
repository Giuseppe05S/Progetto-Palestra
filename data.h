//
// Created by Giuseppe on 28/04/2025.
//
#ifndef DATA_H
#define DATA_H
typedef struct data* Data;

Data creaData(int giorno,int mese,int anno);
Data calcoloDataScadenza(Data data,int durata);
void copiaData(Data data1,Data data2);
void stampaData(Data data);
#endif
