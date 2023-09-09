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
#define ADMIN_PHONE_NUMBER "00000000000"
#define LOGOUT "logout"

typedef struct transaction transaction;
typedef struct client client;
struct transaction/*for saving transactions*/
{
	char partner[MAX_LENGTH];
	char tranType[MAX_LENGTH];
	long int tranQuantity;
	transaction* next;
};
struct client/*structure that we make slients node*/
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