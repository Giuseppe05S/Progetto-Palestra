//
// Created by Giuseppe on 28/04/2025.
//
#include "utils.h"
#include "data.h"
typedef struct iscritto *Iscritto;

Iscritto CreaIscritto(string nome, string cognome, Data dataIscrizione, int durata);
Iscritto getNext(Iscritto is);
string getID(Iscritto is);
void setNext(Iscritto is, Iscritto next);