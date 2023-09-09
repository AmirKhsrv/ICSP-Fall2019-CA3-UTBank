#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

#define USER "user"
#define ADD_USER "add_user"
#define LOGIN "login"
#define DEPOSIT "deposit"
#define WITHDRAW "withdraw"
#define VIEW "view"
#define DELETE "delete"
#define TRANSFER "transfer"
#define VIEW "view"
#define EXIT "exit"
#define USERNAME "username--> "
#define PASSWORD "       password : "
#define PHONE_NUM "       phone_number : "
#define ID "       ID : "
#define BALANCE "       balance : "
#define TRANSACTIONS_NUM "       transactions_count : "
#define TRANSACTIONS_LIST "       transactions_list--> \n"
#define FRONTIER "--------------------------------------------------------------------------\n"
#define CLIENTS_FILE "clients.txt"
#define MAX_LENGTH 60
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "123"
#define PARTNER "\t\tpartner :\t\t"
#define AMOUNT "amount :\t\t"
#define TYPE "type :\n"
#define RECEIVE "receive"
#define SEND "send"

typedef struct transaction transaction;
typedef struct client client;
struct transaction
{
	char partner[MAX_LENGTH];
	char tranType[MAX_LENGTH];
	long int tranQuantity;
	transaction* next;
};
struct client
{
	char name[MAX_LENGTH];
	char password[MAX_LENGTH];
	char phoneNumber[MAX_LENGTH];
	long int id;
	long int balance;
	long int transactionCount;
	transaction* tranList;
	client* next;
};

int addClient(client*);
void startMenu(client*);
void adminMenu(client*);
void clientMenu(client*,char*);
void saveClients(client*);
client* loadClients();
void initialNewClient(client*);
int deleteClient(client*, char*);
int viewClient(client*, char*);
client* findByName(client*, char*);
int depositAndWithdraw(client*, int);
void newtransaction(client*, long int, char*, char*);
void transfer(client*, client*);

///////////////////////////////////////////////////////////
int main()
{
	//int currentState = START_MENU;
	client* clientStart = (client*)malloc(sizeof(client));
	clientStart = loadClients();
	saveClients(clientStart);
	startMenu(clientStart);
	return 0;
}
//////////////////////////////////////////////////////////
void startMenu(client* clientStart)
{
	int undefinedError;
	//system("cls");
	char order[MAX_LENGTH];
	while (1)
	{
		printf("\n\n-----------\n");
		printf("| UT BANK |  you are in SRART menu now------->\n");
		printf("-----------\n\n");
		undefinedError = 0;
		saveClients(clientStart);
		printf("your order--> ");
		scanf("%s", order);
		if (strcmp(order, LOGIN) == 0)
		{
			undefinedError++;
			scanf("%s", order);
			if (strcmp(order, ADMIN_USERNAME) == 0)adminMenu(clientStart);
			else clientMenu(clientStart,order);
			gets();
		}
		if (strcmp(order, EXIT) == 0)
		{
			system("cls");
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@  AMIR MOHAMMAD KHOSRAVI  @\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n HAVE A GOOD DAY \n\n\n\n");
			break;
		}
		if (undefinedError==0)printf("\n!!ERROR!! ( undefined order )\n\n");
	}
}
void adminMenu(client* clientStart)
{
	char clientName[MAX_LENGTH];
	char order[MAX_LENGTH];
	scanf("%s", order);
	if (strcmp(order, ADMIN_PASSWORD) == 0)
	{
		while (1)
		{
			saveClients(clientStart);
			//system("cls");
			printf("\n\n-----------------\n");
			printf("| ADMIN ACCOUNT |  you are in ADMIN account menu now------->\n");
			printf("-----------------\n\n");
			printf("your order--> ");
			scanf("%s", order);
			if (strcmp(order, ADD_USER) == 0)
			{
				addClient(clientStart);
				gets();
			}
			if (strcmp(order, DEPOSIT) == 0)
			{
				scanf("%s", order);
				depositAndWithdraw(findByName(clientStart, order), 1);
				saveClients(clientStart);
				gets();
			}
			if (strcmp(order, WITHDRAW) == 0)
			{
				scanf("%s", order);
				depositAndWithdraw(findByName(clientStart, order), -1);
				saveClients(clientStart);
				gets();
			}
			if (strcmp(order, VIEW) == 0)
			{
				scanf("%s", order);
				if (findByName(clientStart, order))viewClient(clientStart, order);
				else printf("\n!!ERROR!! ( client with this name doesn't exist )\n");
				gets();
			}
			if (strcmp(order, DELETE) == 0)
			{
				scanf("%s", clientName);
				deleteClient(clientStart, clientName);
			}
			if (strcmp(order, EXIT) == 0)break;
		}
	}
	else printf("\n!ERROR! ( admin password is incorrect ) \n");
}
void clientMenu(client* clientStart,char* clientName)
{
	//char clientName[MAX_LENGTH];
	char partnerClient[MAX_LENGTH];
	char order[MAX_LENGTH];
	//scanf("%s", order);
	if (findByName(clientStart, clientName))
	{
		scanf("%s", order);
		if ((strcmp(order, findByName(clientStart, clientName)->password) == 0))
		{
			while (1)
			{
				saveClients(clientStart);
				//system("cls");
				printf("\n\n------------------\n");
				printf("| CLIENT ACCOUNT |  you are in ___ %s ___ account menu now------->\n", findByName(clientStart, clientName)->name);
				printf("------------------\n\n");
				printf("your order--> ");
				scanf("%s", order);
				if (strcmp(order, VIEW) == 0)
				{
					viewClient(clientStart, clientName);
					gets();
				}
				if (strcmp(order, TRANSFER) == 0)transfer(clientStart, findByName(clientStart, clientName));
				if (strcmp(order, EXIT) == 0)break;
			}
		}
		else printf("\n!ERROR! ( %s password is incorrect ) \n", findByName(clientStart, clientName)->name);
	}
	else printf("\n!!ERROR!! ( client with this name doesn't exist )\n");
}
int addClient(client* clientStart)
{
	client* currentClient = clientStart;
	char clientName[MAX_LENGTH];
	while (1)
	{
		if ((currentClient->next) == NULL)
		{
			scanf("%s", clientName);
			if (findByName(clientStart, clientName))
			{
				printf("\n!!ERROR!! ( this username already exists pick another one )\n\n");
				//gets();
				return 0;
			}
			client* newClient = (client*)malloc(sizeof(client));
			currentClient->next = newClient;
			newClient->next = NULL;
			strcpy(newClient->name, clientName);
			scanf("%s", newClient->password);
			scanf("%s", newClient->phoneNumber);
			initialNewClient(newClient);
			newClient->tranList = (transaction*)malloc(sizeof(transaction));
			strcpy(newClient->tranList->partner, "NULL");
			newClient->tranList->tranQuantity = 0;
			strcpy(newClient->tranList->tranType, "NULL");
			newClient->tranList->next = NULL;
			printf("\n@@ client successfuly added @@\n");
			return 1;
		}
		currentClient = currentClient->next;
	}

	return 1;
}
client* loadClients()
{
	int checkFileLoad = 0;
	client* clientStart = (client*)malloc(sizeof(client));
	FILE* clientsFile = fopen(CLIENTS_FILE, "r");
	client* previousClient = (client*)malloc(sizeof(client));
	previousClient = clientStart;
	while (1)
	{
		client* newClient = (client*)malloc(sizeof(client));
		if (fscanf(clientsFile, USERNAME) != 0)break;
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
		transaction* currentTran = (transaction*)malloc(sizeof(transaction)); 
		newClient->tranList= currentTran;
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
		fscanf(clientsFile, FRONTIER);
		previousClient->next = newClient;
		previousClient = newClient;
		checkFileLoad += 1;
	}
	if (checkFileLoad == 0)printf("!!  ERROR ACCURED WHILE DOWNLOADING FILE DATA  !!\n\n");
	else printf("@@  %d CLIENTS FROM FILE SUCCESSFULY DOWNLOADED  @@\n\n", checkFileLoad);
	fclose(clientsFile);
	previousClient->next = NULL;
	return clientStart;
}
void saveClients(client* clientStart)
{
	client* currentClient = clientStart->next;
	FILE* clientsFile = fopen(CLIENTS_FILE, "w");
	while (currentClient != NULL)
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
		transaction* currentTran = (transaction*)malloc(sizeof(transaction)); 
		currentTran=currentClient->tranList;
		fprintf(clientsFile, PARTNER);
		fprintf(clientsFile, AMOUNT);
		fprintf(clientsFile, TYPE);
		currentTran = currentTran->next;
		int counter = currentClient->transactionCount;
		while (counter)
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
		fprintf(clientsFile, FRONTIER);
		currentClient = currentClient->next;
	}
	fclose(clientsFile);
}
void initialNewClient(client* newClient)
{
	newClient->id = time(NULL);
	newClient->balance = 0;
	newClient->transactionCount = 0;
}
int deleteClient(client* clientStart, char* clientName)
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
int viewClient(client* clientStart, char* clientName)
{
	client* currentClient;
	currentClient = clientStart;
	while (1)
	{
		if (strcmp(clientName, currentClient->name) == 0)
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
			transaction* currentTran = (transaction*)malloc(sizeof(transaction));
			currentTran = currentClient->tranList;
			printf(PARTNER);
			printf(AMOUNT);
			printf(TYPE);
			currentTran = currentTran->next;
			int counter = currentClient->transactionCount;
			while (counter)
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
client* findByName(client* clientStart, char* clientName)
{
	client* currentClient;
	currentClient = clientStart;
	while (currentClient != NULL)
	{
		if (strcmp(clientName, currentClient->name) == 0)return currentClient;
		currentClient = currentClient->next;
	}
	return NULL;
}
int depositAndWithdraw(client* choosedClient, int sign)
{
	if (choosedClient == NULL)
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
	choosedClient->balance += sign*amount;
	choosedClient->transactionCount += 1;
	if (sign == 1)newtransaction(choosedClient, amount, DEPOSIT, ADMIN_USERNAME);
	else newtransaction(choosedClient, amount, WITHDRAW, ADMIN_USERNAME);
	saveClients(choosedClient);
	printf("\n@@ successfuly done @@\n\n");
}
void newtransaction(client* choosedClient, long int tranQuantity, char* tranType, char* partner)
{
	transaction* tranNew = (transaction*)malloc(sizeof(transaction));
	transaction* currentTran = (transaction*)malloc(sizeof(transaction)); 
	currentTran=choosedClient->tranList;
	while (currentTran != NULL)
	{
		if (currentTran->next == NULL)
		{
			currentTran->next = tranNew;
			break;
		}
		currentTran = currentTran->next;
	}
	strcpy(tranNew->tranType, tranType);
	printf("%s", tranType);
	tranNew->tranQuantity = tranQuantity;
	strcpy(tranNew->partner, partner);
	tranNew->next = NULL;
}
void transfer(client* clientStart, client* activeClient)
{
	int moneyAmount;
	char partnerClient[MAX_LENGTH];
	char order[MAX_LENGTH];
	scanf("%s", order);
	if (findByName(clientStart, order))
	{
		strcpy(partnerClient, order);
		if (scanf("%ld", &moneyAmount))
		{
			if (moneyAmount <= activeClient->balance)
			{
				activeClient->balance -= moneyAmount;
				findByName(clientStart, partnerClient)->balance += moneyAmount;
				activeClient->transactionCount += 1;
				findByName(clientStart, partnerClient)->transactionCount += 1;
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
	gets();
}