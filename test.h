//
// Created by Giuseppe on 27/05/2025.
//

#ifndef TEST_H
#define TEST_H

typedef struct hash* hashtable;
typedef struct c_listP *listP;
typedef struct c_list *list;

typedef char *string;
void mainTest(hashtable hClienti,list lCorsi, listP lPrenotazioni);
//int testCorrettaRegistrazionePrenotazione(string input,string output,string oracle, hashtable hClienti,list lCorsi);
int confrontaFile(string file1,string file2);


#endif //TEST_H
