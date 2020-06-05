#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#include "Input.h"
#include "Date.h"
#include "GravesList.h"
#include "Header.h"
#include "File.h"


t_Grave* add_new_grave(t_List list, const char* gravesList_file_path, t_CemeterySize cemSize, float gravePrice)
{
	FILE* fp = fopen(gravesList_file_path, "a");
	if (fp == NULL)
	{
		printf("File cannot be opened!\n");
	}

	t_Grave* grave = (t_Grave*)malloc(sizeof(t_Grave));

	char personalNumber[PN_DATE_SIZE] = "";
	printf("\nPersonal number: ");
	scanf("%s", &personalNumber);
	fseek(stdin, 0, SEEK_SET);

	if (findPersonalNumber(list.head, personalNumber) != NULL)
	{
		return NULL;
	}

	strcpy(grave->person.personalNumber, personalNumber);

	//Add names
	printf("First name: ");
	fgets(grave->person.firstName, NAME_SIZE, stdin);
	grave->person.firstName[strlen(grave->person.firstName) - 1] = '\0';
	fseek(stdin, 0, SEEK_SET);

	printf("Last name: ");
	fgets(grave->person.lastName, NAME_SIZE, stdin);
	grave->person.lastName[strlen(grave->person.lastName) - 1] = '\0';
	fseek(stdin, 0, SEEK_SET);

	//Add location
	printf("\nThis cemetery has %d rows and %d columns.", cemSize.rows, cemSize.cols);
	boolean isFree = F;
	eResult isValid = invalid;

	while (isFree != T || isValid != valid)
	{
		printf("\nEnter location (row-column): ");
		scanf("%d-%d", &grave->location.row, &grave->location.col);
		fseek(stdin, 0, SEEK_SET);

		isFree = isLocationFree(&grave->location, list.head);

		if ((grave->location.col > cemSize.cols || grave->location.col < 0)
			|| (grave->location.row > cemSize.rows || grave->location.row < 0))
		{
			printf("\nThe cemetery doesn't contain the given location.");
			isValid = invalid;
		}
		else
		{
			isValid = valid;
		}
		if (isFree == F)
		{
			printf("This location is not free!");
		}
	}


	grave->person.deathDate = add_date("Death date");

	//Grave price
	char answer[4] = "";
	eResult isValidAnswer = invalid;
	printf("\nThe price of the grave is %.2f. ", gravePrice);
	grave->price = gravePrice;
	while (isValidAnswer != valid)
	{
		printf("\nDo you want to buy it? (Yes/No) - ");
		scanf("%s", &answer);
		if (compare_strings(answer, "Yes"))
		{
			strcpy(grave->endDate, "forever");
			grave->paymentStatus = Paid;
			break;
		}
		else if (compare_strings(answer, "No"))
		{
			strcpy(grave->endDate, "15");
			grave->paymentStatus = Unpaid;
			printf("\nThe grave is reserved for 15 years.\n");
			break;
		}
		else
		{
			printf("\nInvalid answer!\n");
			isValidAnswer = invalid;
		}
	}

	fprintf(fp, "%d/%d/%d | %s | %s | %s | %d-%d | %.2f | %d | %s\n",
		grave->person.deathDate.day,
		grave->person.deathDate.month,
		grave->person.deathDate.year,

		grave->person.personalNumber,
		grave->person.firstName,
		grave->person.lastName,

		grave->location.row,
		grave->location.col,

		grave->price,
		grave->paymentStatus,
		grave->endDate);

	return grave;
}

boolean isLocationFree(t_Location* location, t_Node* p_head)
{
	t_Node* current = p_head;
	if (p_head == NULL)
	{
		return T;
	}

	eResult result = invalid;
	t_Location currentLocation = current->payload.location;

	while (current != NULL)
	{
		if (current->payload.location.row == location->row
			&& current->payload.location.col == location->col)
		{
			if (compare_strings(current->payload.endDate, "forever") != T)
			{
				time_t nowTime = time(NULL);
				struct tm* tm = localtime(&nowTime);
				t_Date nowDate = { 0 };
				nowDate.day = tm->tm_mday;
				nowDate.month = tm->tm_mon + 1;
				nowDate.year = tm->tm_year + 1900;

				t_Date diff = calculateDiff(current->payload.person.deathDate, nowDate);

				if (diff.year < 15)
				{
					return F;
				}
				else
				{
					return T;
				}
			}
			else
			{
				return F;
			}
		}
		else
		{
			current = current->next;
		}
	}
	return T;
}

void addGravePrice(t_CemeteryOwner* cemeteryOwner)
{
	printf("\nPrice per grave: ");
	scanf("%f", cemeteryOwner->gravePrice);
}


// Write cemetery owner datas in txt file.
void registerCemeteryOwner(const char* file_path)
{
	t_CemeteryOwner* cemeteryOwner = malloc((t_CemeteryOwner*)sizeof(t_CemeteryOwner));
	char* string = { 0 };

	char* cemeterySizeStr = malloc((char*)sizeof(char));
	printf("\nUsername: ");
	scanf("%s", &cemeteryOwner->username);
	printf("\nPassword: ");
	scanf("%s", &cemeteryOwner->password);
	printf("\nPrice per grave: ");
	scanf("%f", &cemeteryOwner->gravePrice);
	printf("\nRows in the cemetery: ");
	scanf("%d", &cemeteryOwner->cemeterySize.rows);
	printf("\nColumns in the cemetery: ");
	scanf("%d", &cemeteryOwner->cemeterySize.cols);

	FILE* fp = createFile(file_path);
	fp = fopen(file_path, "w");
	fprintf(fp, " %s | %s | %.2f | %d - %d",
		cemeteryOwner->username, cemeteryOwner->password,
		cemeteryOwner->gravePrice,
		cemeteryOwner->cemeterySize.rows, cemeteryOwner->cemeterySize.cols);
	fclose(fp);
	free(cemeteryOwner);
}

t_Node* findPersonalNumber(t_Node* p_head, const char* personalNumber)
{
	t_Node* current = p_head;

	if (p_head == NULL)
	{
		return NULL;
	}
	while (compare_strings(current->payload.person.personalNumber, personalNumber) != T)
	{
		if (current->next == NULL)
		{
			return NULL;
		}
		else
		{
			current = current->next;
		}
	}
	return current;
}
