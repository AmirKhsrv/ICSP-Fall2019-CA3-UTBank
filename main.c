#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include"admin_issues.h"/*functions that are related to admin such as orders and functions*/

int main()
{
	client* clientStart = (client*)malloc(sizeof(client));
	clientStart = loadClients();
	saveClients(clientStart);
	startMenu(clientStart);/*start menu is the manu that every one have access*/
	return 0;
}