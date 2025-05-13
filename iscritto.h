//
// Created by Giuseppe on 28/04/2025.
//
#ifndef ISCRITTO_H
#define ISCRITTO_H

#include "utils.h"
#include "data.h"

typedef struct iscritto *Iscritto;

Iscritto CreaIscritto(string nome, string cognome, Data dataIscrizione, int durata,string ID);
Iscritto getNext(Iscritto is);
string getID(Iscritto is);
void setNext(Iscritto is, Iscritto next);
#endif