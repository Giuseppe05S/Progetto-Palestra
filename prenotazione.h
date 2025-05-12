//
// Created by Giuseppe on 28/04/2025.
//

typedef struct prenotazione *Prenotazione;

//Crea una prenotazione
Prenotazione creaPrenotazione(string IDPrenotazione, string IDCorso, string IDCliente, Data dataPrenotazione);

//Elima una determinata prenotazione
void eliminaPrenotazione(Prenotazione pr);

//Stampa gli attributi della struttura prenotazione
void stampaPrenotazione(Prenotazione p);