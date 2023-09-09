#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include"client_issues.h"

int addClient(client*);
void adminMenu(client*);
void initialNewClient(client*);
int deleteClient(client*, char*);
int depositAndWithdraw(client*, int);
int ifAddDelete(char*, client*, char*);
int ifDepositWithdraw(char*, client*);
int ifView(char*, client*);
void adminAccountFirstText(client*);
void makeNewClient(client*,client*, char*);
