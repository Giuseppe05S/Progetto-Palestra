//
// Created by Giuseppe on 28/04/2025.
//
#ifndef ISCRITTO_H
#define ISCRITTO_H

#include "utils.h"
#include "data.h"
#include <stdio.h>

typedef struct iscritto *Iscritto;

Iscritto CreaIscritto(string nome, string cognome, Data dataIscrizione, int durata,string ID);
Iscritto getNext(Iscritto is);
void stampaCliente(Iscritto is);
void stampaMinimaCliente(Iscritto is);
string getID(Iscritto is);
string getNome(Iscritto is);
string getCognome(Iscritto is);
int getDurata(Iscritto is);
void setNext(Iscritto is, Iscritto next);
void rinnovaAbbonamento(Iscritto is, int durata);
void eliminaIscritto(Iscritto is);
int controlloAbbonamento(Iscritto is);
void scriviCliente(Iscritto is,FILE *fp);
#endif