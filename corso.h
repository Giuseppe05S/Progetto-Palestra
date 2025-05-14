//
// Created by Giuseppe on 28/04/2025.
//
#ifndef CORSO_H
#define CORSO_H

#include "utils.h"
#include "data.h"


typedef struct corso *Corso;

Corso CreaCorso(string ID, string nome, Data dataLezione, string orario);
void stampaCorso(Corso co);
int Disponibilita(Corso co);

#endif