#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include"defines_structs.h"

void startMenu(client*);
void saveClients(client*);
client* loadClients();
int viewClient(client*, char*);
client* findByName(client*, char*);
void newtransaction(client*, long int, char*, char*);
//int getTransactionList(FILE*, client*, client*);
//int getClientData(FILE*, client*,int*);
