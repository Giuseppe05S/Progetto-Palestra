//
// Created by Giuseppe on 28/04/2025.
//
typedef struct data* Data;

Data creaData(int giorno,int mese,int anno);
Data calcoloDataScadenza(Data data,int durata);
void stampaData(Data data);