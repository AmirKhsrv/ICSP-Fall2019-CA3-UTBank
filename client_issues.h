#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include"general_issues.h"

void clientMenu(client* const, char*);
void transfer(client*, client*);
void clientAccountFirstText(client*, char*);
int ifViewTransfer(char*, client*, char*);