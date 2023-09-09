#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include"admin_issues.h"

void adminMenu(client* clientStart) /*if user input */
{
	int undefinedError;
	char flush;
	char clientName[MAX_LENGTH];/*aimed client name will be saved here*/
	char order[MAX_LENGTH];
	scanf("%s", order);
	if (strcmp(order, ADMIN_PASSWORD) == 0)/*if admin password is correctly entered*/
	{
		while (1)/*be in admin account till he or she enter logout*/
		{
			undefinedError = 0;
			adminAccountFirstText(clientStart);
			scanf("%s", order);
			undefinedError+=ifAddDelete(order,clientStart,clientName);/*if order is add or delete*/
			undefinedError+=ifDepositWithdraw(order, clientStart);/*if input is deposit or withdraw*/
			undefinedError+=ifView(order,clientStart);/*if order is view*/
			if (strcmp(order, LOGOUT) == 0)break;
			if (undefinedError == 0)
			{
				while ((flush = getchar()) != '\n');/*flush the buffer*/
				printf("\n!!ERROR!! ( undefined order )\n\n");
			}
		}
	}
	else printf("\n!ERROR! ( admin password is incorrect ) \n");
}
int addClient(client* clientStart)/*adding clients*/
{
	char flush;/*to flush a buffer*/
	client* currentClient = clientStart;
	char clientName[MAX_LENGTH];
	while (1)/*seek to the next of clients node list*/
	{
		if ((currentClient->next) == NULL)
		{
			scanf("%s", clientName);
			if (findByName(clientStart, clientName))/*check if there is no one with this username in list*/
			{
				printf("\n!!ERROR!! ( this username already exists pick another one )\n\n");
				while ((flush = getchar()) != '\n');/*flush the buffer*/
				return 0;
			}
			makeNewClient(clientStart,currentClient,clientName);/*create new clent*/
			return 1;
		}
		currentClient = currentClient->next; 
	}
	return 1;
}
int deleteClient(client* clientStart, char* clientName)/*delete clients*/
{
	client* currentClient;// = (client*)malloc(sizeof(client));
	client* previousClient;// = (client*)malloc(sizeof(client));
	currentClient = clientStart->next;
	previousClient = clientStart;
	while (currentClient != NULL)
	{
		if (strcmp(clientName, currentClient->name) == 0)
		{
			previousClient->next = currentClient->next;
			free(currentClient->tranList);/*risky @@@@@@@@*/
			free(currentClient);
			printf("\n@@ client deleted successfuly @@\n\n");
			return 1;
		}
		currentClient = currentClient->next;
		previousClient = previousClient->next;
	}
	printf("\n!! ERROR !! ( there is no client with this username )\n\n");
	saveClients(clientStart);
}
int depositAndWithdraw(client* choosedClient, int sign)/*if admin order is deposit or withdraw*/
{
	if (choosedClient == NULL)/*maybe client doesnt exist*/
	{
		printf("\n!!ERROR!! ( couldnt find client )\n\n");
		return 0;
	}
	long int amount;
	if (scanf("%d", &amount) == 0)
	{
		printf("\n!!ERROR!! ( please enter a number )\n\n");
		return 0;
	}
	if((choosedClient->balance < amount)&&(sign==-1))
	{
		printf("\n!!ERROR!! ( client doesnt have enough money clients account balance is : %ld )\n\n", choosedClient->balance);
		return 0;
	}
	choosedClient->balance += sign*amount;
	choosedClient->transactionCount += 1;
	if (sign == 1)newtransaction(choosedClient, amount, DEPOSIT, ADMIN_USERNAME);/*if sign is + we will deposit and if its - we will withdraw*/
	else newtransaction(choosedClient, amount, WITHDRAW, ADMIN_USERNAME);
	saveClients(choosedClient);
	printf("\n@@ successfuly done @@\n\n");
}
void initialNewClient(client* newClient)/*initialize new clients such as id balance and transaction count*/
{
	newClient->id = time(NULL);/*we initaial ID with time*/
	newClient->balance = 0;
	newClient->transactionCount = 0;
}
int ifAddDelete(char* order, client* clientStart,char* clientName)/*if admin order is add or delete*/
{
	char flush;
	int undefinedError;
	undefinedError = 0;
	if (strcmp(order, ADD_USER) == 0)
	{
		undefinedError++;
		addClient(clientStart);/*adding new clients*/
		while ((flush = getchar()) != '\n');/*clear buffer*/
	}
	if (strcmp(order, DELETE) == 0)
	{
		undefinedError++;
		scanf("%s", clientName);
		deleteClient(clientStart, clientName);/*deleting clients*/
	}
	return undefinedError;
}
int ifDepositWithdraw(char* order,client* clientStart)/*check is admin's input is deposit or withdraw*/
{
	char flush;
	int undefinedError;
	undefinedError = 0;
	if (strcmp(order, DEPOSIT) == 0)
	{
		undefinedError++;
		scanf("%s", order);
		depositAndWithdraw(findByName(clientStart, order), 1);/*depositing to a client account*/
		saveClients(clientStart);
		while ((flush = getchar()) != '\n');
	}
	if (strcmp(order, WITHDRAW) == 0)
	{
		undefinedError++;
		scanf("%s", order);
		depositAndWithdraw(findByName(clientStart, order), -1);/*withdraw from a client account*/
		saveClients(clientStart);
		while ((flush = getchar()) != '\n');/*clear the stdin buffer*/
	}
	return undefinedError;
}
int ifView(char* order, client* clientStart)/*if input of client is view*/
{
	char flush;
	int undefinedError;/*we use these in function and return them for showing error if its wrong input*/
	undefinedError = 0;
	if (strcmp(order, VIEW) == 0)
	{
		undefinedError++;
		scanf("%s", order);
		if (findByName(clientStart, order))viewClient(clientStart, order);
		else printf("\n!!ERROR!! ( client with this name doesn't exist )\n");
		while ((flush = getchar()) != '\n');
	}
	return undefinedError;
}
void adminAccountFirstText(client* clientStart)/*first text in admin account*/
{
	saveClients(clientStart);
	//system("cls");
	printf("\n\n-----------------\n");
	printf("| ADMIN ACCOUNT |  you are in ADMIN account menu now------->\n");
	printf("-----------------\n\n");
	printf("your order--> ");
}
void makeNewClient(client* startClient,client* currentClient, char* clientName)/*we make new clients here*/
{
	char tempPhoneNumber[MAX_LENGTH];
		client* newClient = (client*)malloc(sizeof(client));
		client* tempClient= startClient;
		currentClient->next = newClient;
		newClient->next = NULL;
		strcpy(newClient->name, clientName);
		scanf("%s", newClient->password);
		scanf("%s", tempPhoneNumber);
		while (1)/*we check in this loop if there is another client with this name before*/
		{
			if (strcmp(tempClient->phoneNumber, tempPhoneNumber) == 0)/*check previous account username wth new if there is no equality*/
			{
				printf("\n!!ERROR!! ( this phone number belongs to another client please choose another one )\n\nnew phone number--->");
				scanf("%s", tempPhoneNumber);
				tempClient = startClient;
			}
			tempClient = tempClient->next;
			if (tempClient == NULL)break;
		}
		strcpy(newClient->phoneNumber, tempPhoneNumber);/*initializing new client's transaction list data*/
		initialNewClient(newClient);
		newClient->tranList = (transaction*)malloc(sizeof(transaction));
		strcpy(newClient->tranList->partner, "NULL");
		newClient->tranList->tranQuantity = 0;
		strcpy(newClient->tranList->tranType, "NULL");
		newClient->tranList->next = NULL;
		printf("\n@@ client successfuly added @@\n");
}