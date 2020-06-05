#pragma once

#include<stdio.h>

// Personal number and date size
#define PN_DATE_SIZE ((size_t) 11)
#define NAME_SIZE ((size_t) 20)
#define LOCATION_STR_SIZE ((size_t) 10)
#define END_DATE_SIZE ((size_t) 8)

typedef struct
{
	int rows;
	int cols;
} t_CemeterySize;

typedef struct
{
	char username[NAME_SIZE];
	char password[NAME_SIZE];
	t_CemeterySize cemeterySize;
	float gravePrice;
} t_CemeteryOwner;


//DATE
typedef enum
{
	normal, leap
} eIsLeap;

typedef struct
{
	int day;
	int month;
	int year;
} t_Date;

//PERSON
typedef struct Person
{
	char personalNumber[PN_DATE_SIZE];
	char firstName[NAME_SIZE];
	char lastName[NAME_SIZE];
	t_Date deathDate;
} t_Person;

//GRAVE
typedef struct Location
{
	int row;
	int col;
} t_Location;

typedef enum PaymentStatus
{
	Unpaid, Paid
} ePaymentStatus;

typedef struct Grave
{
	t_Location location;
	float price;
	ePaymentStatus paymentStatus;
	char endDate[END_DATE_SIZE];
	t_Person person;
} t_Grave;


//LIST
typedef struct Node
{
	t_Grave payload;
	struct Node* next;
} t_Node;

typedef struct List
{
	struct t_Node* head;
} t_List;

typedef enum
{
	F, T
} boolean;

//Validation
typedef enum
{
	invalid, valid
} eResult;