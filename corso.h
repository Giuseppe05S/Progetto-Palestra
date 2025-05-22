//
// Created by Giuseppe on 28/04/2025.
//
#ifndef CORSO_H
#define CORSO_H

#include "utils.h"
#include "data.h"
#include <stdio.h>

typedef struct corso *Corso;
typedef struct orario *Orario;

Corso creaCorso(string ID, string nome, Data dataLezione, int ora,int minuti,int nPartecipanti);
void stampaCorso(Corso co);
int Disponibilita(Corso co);
string getIDCorso(Corso co);
string getNomeCorso(Corso co);
Data getDataCorso(Corso co);
Orario getOrario(Corso co);
int confrontaOrario(Orario o1, Orario o2);
Orario creaOrario(int ora,int minuti);
void scriviCorso(Corso co,FILE *fp);
void incrementaPartecipanti(Corso co);

#endif