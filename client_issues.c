#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include"client_issues.h"

void clientMenu(client* const clientStart, char* clientName)/*if clients login to their account they will come to this function and state*/
{
	char flush;
	int undefinedError;
	char partnerClient[MAX_LENGTH];/*the client that we have transaction with*/
	char order[MAX_LENGTH];/*we save input of user in this array*/
	if (findByName(clientStart, clientName))/*if there is a username with this user name*/
	{
		scanf("%s", order);
		if ((strcmp(order, findByName(clientStart, clientName)->password) == 0))/*check if the input password matches to the username*/
		{
			while (1)/*get user inputs till he or she enter logout*/
			{
				undefinedError = 0;
				clientAccountFirstText(clientStart, clientName);/*first text in client account*/
				scanf("%s", order);
				undefinedError=ifViewTransfer(order,clientStart,clientName);/*transfering money*/
				if (strcmp(order, LOGOUT) == 0)break;
				if (undefinedError == 0)
				{
					while ((flush = getchar()) != '\n');
					printf("\n!!ERROR!! ( undefined order )\n\n");
				}
			}
		}
		else printf("\n!ERROR! ( %s password is incorrect ) \n", findByName(clientStart, clientName)->name);
	}
	else printf("\n!!ERROR!! ( client with this name doesn't exist )\n");
}
void transfer(client* clientStart, client* activeClient)/*transferin money*/
{
	char flush;/*used to flush the buffer if input is invalid*/
	int moneyAmount;
	char partnerClient[MAX_LENGTH];
	char order[MAX_LENGTH];
	scanf("%s", order);
	if (findByName(clientStart, order))/*if aimed user exists*/
	{
		strcpy(partnerClient, order);
		if (scanf("%ld", &moneyAmount))/*if input is a number*/
		{
			if (moneyAmount <= activeClient->balance)/*if user have enough money*/
			{
				activeClient->balance -= moneyAmount;
				findByName(clientStart, partnerClient)->balance += moneyAmount;/*adding money*/
				activeClient->transactionCount += 1;
				findByName(clientStart, partnerClient)->transactionCount += 1;/*loosing money*/
				newtransaction(activeClient, moneyAmount, SEND, partnerClient);
				newtransaction(findByName(clientStart, partnerClient), moneyAmount, RECEIVE, activeClient->name);
				saveClients(clientStart);
				printf("\n@@ transfered successfuly @@n\n");
			}
			else printf("\n!!ERROR!! ( you don't have enough money .your account balance is : %ld )\n\n", activeClient->balance);
		}
		else printf("\n!!ERROR!! ( please enter a number )\n\n");
	}
	else printf("\n!!ERROR!! ( client with this name doesn't exist )\n");
	while ((flush = getchar()) != '\n');
}
void clientAccountFirstText(client* clientStart,char* clientName)/*client first text*/
{
	saveClients(clientStart);/*saving changes*/
	//system("cls");
	printf("\n\n------------------\n");
	printf("| CLIENT ACCOUNT |  you are in ___ %s ___ account menu now------->\n", findByName(clientStart, clientName)->name);
	printf("------------------\n\n");
	printf("your order--> ");
}
int ifViewTransfer(char* order, client* clientStart,char* clientName)/*if client input is view or transfer*/
{
	char flush;
	int undefinedError;
	undefinedError = 0;
	if (strcmp(order, VIEW) == 0)/*if its view*/
	{
		undefinedError++;
		viewClient(clientStart, clientName);
		while ((flush = getchar()) != '\n');
	}
	if (strcmp(order, TRANSFER) == 0)/*if its transfer*/
	{
		undefinedError++;
		transfer(clientStart, findByName(clientStart, clientName));
	}
	return undefinedError;
}