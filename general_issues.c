#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include"general_issues.h"

void startMenu(client* clientStart)
{
	int undefinedError;/*used to print errors properly*/
	//system("cls");
	char order[MAX_LENGTH];/*we save user inputs in this array*/
	char flush;/*we use this this to flush the buffer when input is invalid*/
	while (1)
	{
		printf("\n\n-----------\n");
		printf("| UT BANK |  you are in SRART menu now------->\n");
		printf("-----------\n\n");
		undefinedError = 0;
		saveClients(clientStart);/*save changes till now*/
		printf("your order--> ");
		scanf("%s", order);
		if (strcmp(order, LOGIN) == 0)
		{
			undefinedError++;
			scanf("%s", order);
			if (strcmp(order, ADMIN_USERNAME) == 0)adminMenu(clientStart);/*login to admin account*/
			else
			{
				int a = 600;
				client* temp = clientStart;/*for unknown error I saved clientStart in a temp*/
				clientMenu(clientStart, order);
				clientStart = temp;
			}
			while ((flush = getchar()) != '\n');/*flushing the stdin buffer*/
		}
		if (strcmp(order, EXIT) == 0)
		{
			system("cls");
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@  AMIR MOHAMMAD KHOSRAVI  @\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n HAVE A GOOD DAY \n\n\n\n");
			break;
		}
		if (undefinedError == 0)/*if none of other orders are done*/
		{
			while ((flush = getchar()) != '\n');
			printf("\n!!ERROR!! ( undefined order )\n\n");
		}
	}
}
client* loadClients()/*download clients data from text file*/
{
	int checkFileLoad = 0;
	client* clientStart = (client*)malloc(sizeof(client));
	FILE* clientsFile = fopen(CLIENTS_FILE, "r");
	client* previousClient = (client*)malloc(sizeof(client));//eeeeeeeenja
	previousClient = clientStart;
	//getClientData(clientsFile,previousClient,checkFileLoad);
	while (1)/*get clients till the last of them*/
	{
		client* newClient = (client*)malloc(sizeof(client));
		if (fscanf(clientsFile, USERNAME) != 0)break;/*if there is no user anymore break the loop and dont get users anymore*/
		fscanf(clientsFile, "%s", newClient->name);
		fscanf(clientsFile, PASSWORD);
		fscanf(clientsFile, "%s", newClient->password);
		fscanf(clientsFile, PHONE_NUM);
		fscanf(clientsFile, "%s", newClient->phoneNumber);
		fscanf(clientsFile, ID);
		fscanf(clientsFile, "%ld", &newClient->id);
		fscanf(clientsFile, BALANCE);
		fscanf(clientsFile, "%ld", &newClient->balance);
		fscanf(clientsFile, TRANSACTIONS_NUM);
		fscanf(clientsFile, "%ld", &newClient->transactionCount);
		fscanf(clientsFile, TRANSACTIONS_LIST);
		fscanf(clientsFile, PARTNER);
		fscanf(clientsFile, AMOUNT);
		fscanf(clientsFile, TYPE);
		transaction* currentTran = (transaction*)malloc(sizeof(transaction));/*used to get transaction list of each client*/
		newClient->tranList = currentTran;
		int counter = newClient->transactionCount;
		while (counter)/*geting transaction data till the end of them*/
		{
			transaction* tranNew = (transaction*)malloc(sizeof(transaction));
			currentTran->next = tranNew;
			fscanf(clientsFile, "\t\t%s\t\t\t", tranNew->partner);
			fscanf(clientsFile, "%ld\t\t\t", &tranNew->tranQuantity);
			fscanf(clientsFile, "%s\n", tranNew->tranType);
			counter--;
			currentTran = currentTran->next;
		}
		currentTran->next = NULL;
		fscanf(clientsFile, FRONTIER);/*get the frontier between clients data*/
		previousClient->next = newClient;
		previousClient = newClient;
		checkFileLoad += 1;
	}
	if (checkFileLoad == 0)printf("!!  ERROR ACCURED WHILE DOWNLOADING FILE DATA  !!\n\n");/*if file data downloaded successfuly*/
	else printf("@@  %d CLIENTS FROM FILE SUCCESSFULY DOWNLOADED  @@\n\n", checkFileLoad);
	fclose(clientsFile);
	previousClient->next = NULL;
	return clientStart;/*return head of clients nodes*/
}
void saveClients(client* clientStart)/*to save clients data if file*/
{
	client* currentClient = clientStart->next;
	FILE* clientsFile = fopen(CLIENTS_FILE, "w");
	while (currentClient != NULL)/*till the end of clients save clients*/
	{
		fprintf(clientsFile, USERNAME);
		fprintf(clientsFile, "%s\n", currentClient->name);
		fprintf(clientsFile, PASSWORD);
		fprintf(clientsFile, "%s\n", currentClient->password);
		fprintf(clientsFile, PHONE_NUM);
		fprintf(clientsFile, "%s\n", currentClient->phoneNumber);
		fprintf(clientsFile, ID);
		fprintf(clientsFile, "%ld\n", currentClient->id);
		fprintf(clientsFile, BALANCE);
		fprintf(clientsFile, "%ld\n", currentClient->balance);
		fprintf(clientsFile, TRANSACTIONS_NUM);
		fprintf(clientsFile, "%ld\n", currentClient->transactionCount);
		fprintf(clientsFile, TRANSACTIONS_LIST);
		transaction* currentTran = (transaction*)malloc(sizeof(transaction));/*save transactions to the text file */
		currentTran = currentClient->tranList;
		fprintf(clientsFile, PARTNER);
		fprintf(clientsFile, AMOUNT);
		fprintf(clientsFile, TYPE);
		currentTran = currentTran->next;
		int counter = currentClient->transactionCount;
		while (counter)/*save transaction till the number of transactions is 0*/
		{
			fprintf(clientsFile, "\t\t%s\t\t\t", currentTran->partner);
			fprintf(clientsFile, "%ld\t\t\t", currentTran->tranQuantity);
			fprintf(clientsFile, "%s\n", currentTran->tranType);
			if (currentTran->next == NULL)
			{
				break;
			}
			currentTran = currentTran->next;
			counter--;
		}
		fprintf(clientsFile, FRONTIER);/*print frontiers between clients data*/
		currentClient = currentClient->next;
	}
	fclose(clientsFile);
}
int viewClient(client* clientStart, char* clientName)/*view choosed clients*/
{
	client* currentClient;
	currentClient = clientStart;
	while (1)/*check all users if they are equal to choosed client*/
	{
		if (strcmp(clientName, currentClient->name) == 0)/*if choosed name exists in clients list*/
		{
			printf("\n");
			printf(FRONTIER);
			printf(USERNAME);
			printf("%s\n", currentClient->name);
			printf(PASSWORD);
			printf("%s\n", currentClient->password);
			printf(PHONE_NUM);
			printf("%s\n", currentClient->phoneNumber);
			printf(ID);
			printf("%ld\n", currentClient->id);
			printf(BALANCE);
			printf("%ld\n", currentClient->balance);
			printf(TRANSACTIONS_NUM);
			printf("%ld\n", currentClient->transactionCount);
			printf(TRANSACTIONS_LIST);
			transaction* currentTran = (transaction*)malloc(sizeof(transaction));/*show transactions of client*/
			currentTran = currentClient->tranList;
			printf(PARTNER);
			printf(AMOUNT);
			printf(TYPE);
			currentTran = currentTran->next;
			int counter = currentClient->transactionCount;
			while (counter)/*show all of transactions*/
			{
				printf("\t\t%s\t\t\t", currentTran->partner);
				printf("%ld\t\t\t", currentTran->tranQuantity);
				printf("%s\n", currentTran->tranType);
				if (currentTran->next == NULL)
				{
					break;
				}
				currentTran = currentTran->next;
				counter--;
			}
			printf(FRONTIER);
			return 0;
		}
		if (currentClient->next == NULL)break;
		currentClient = currentClient->next;
	}
}
client* findByName(client* clientStart, char* clientName)/*we pass the client's name and we will get address of that client*/
{
	client* currentClient;
	currentClient = clientStart;
	while (currentClient != NULL)
	{
		if (strcmp(clientName, currentClient->name) == 0)return currentClient;/*if client name is equal to one we return its structs address*/
		currentClient = currentClient->next;
	}
	return NULL;/*if there is no matching client we return null*/
}
void newtransaction(client* choosedClient, long int tranQuantity, char* tranType, char* partner)/*make and save a new transaction*/
{
	transaction* tranNew = (transaction*)malloc(sizeof(transaction));
	transaction* currentTran = (transaction*)malloc(sizeof(transaction));//een
	currentTran = choosedClient->tranList;
	while (currentTran != NULL)
	{
		if (currentTran->next == NULL)
		{
			currentTran->next = tranNew;/*making new transaction*/
			break;
		}
		currentTran = currentTran->next;
	}
	strcpy(tranNew->tranType, tranType);/*saving transaction data*/
	tranNew->tranQuantity = tranQuantity;
	strcpy(tranNew->partner, partner);
	tranNew->next = NULL;
}
/*
int getClientData(FILE* clientsFile, client* previousClient,int* checkFileLoad)
{
	while (1)
	{
		client* newClient = (client*)malloc(sizeof(client));
		if (fscanf(clientsFile, USERNAME) != 0)return *checkFileLoad;
		fscanf(clientsFile, "%s", newClient->name);
		fscanf(clientsFile, PASSWORD);
		fscanf(clientsFile, "%s", newClient->password);
		fscanf(clientsFile, PHONE_NUM);
		fscanf(clientsFile, "%s", newClient->phoneNumber);
		fscanf(clientsFile, ID);
		fscanf(clientsFile, "%ld", &newClient->id);
		fscanf(clientsFile, BALANCE);
		fscanf(clientsFile, "%ld", &newClient->balance);
		fscanf(clientsFile, TRANSACTIONS_NUM);
		fscanf(clientsFile, "%ld", &newClient->transactionCount);
		fscanf(clientsFile, TRANSACTIONS_LIST);
		fscanf(clientsFile, PARTNER);
		fscanf(clientsFile, AMOUNT);
		fscanf(clientsFile, TYPE);
		getTransactionList(clientsFile, newClient, previousClient);
		fscanf(clientsFile, FRONTIER);
		previousClient->next = newClient;
		previousClient = newClient;
		*checkFileLoad += 1;
	}
}
int getTransactionList(FILE* clientsFile, client* newClient, client* previousClient)
{
	transaction* currentTran = (transaction*)malloc(sizeof(transaction));
	newClient->tranList = currentTran;
	int counter = newClient->transactionCount;
	while (counter)
	{
		transaction* tranNew = (transaction*)malloc(sizeof(transaction));
		currentTran->next = tranNew;
		fscanf(clientsFile, "\t\t%s\t\t\t", tranNew->partner);
		fscanf(clientsFile, "%ld\t\t\t", &tranNew->tranQuantity);
		fscanf(clientsFile, "%s\n", tranNew->tranType);
		counter--;
		currentTran = currentTran->next;
	}
	currentTran->next = NULL;
	return 1;
}*/
