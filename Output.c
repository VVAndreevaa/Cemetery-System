#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include "Output.h"
#include "Input.h"
#include "File.h"
#include "GravesList.h"
#include "Date.h"

t_CemeterySize cemeterySizeG = { 0, 0 };
float gravePriceG = 0.0;

void showMenu(const char* gravesList_file_path, const char* cemeteryOwner_file_path, t_List* list)
{
	FILE* file = fopen(cemeteryOwner_file_path, "r");
	if ((file == NULL) || fgetc(file) == EOF)
	{
		cemeteryOwnerMenu(cemeteryOwner_file_path, gravesList_file_path, list);
	}
	else
	{
		addDataToList("gravesList.txt", list);

		t_CemeteryOwner cemeteryOwnerTemp = { 0 };
		t_CemeterySize cemeterySizeTemp = { 0 };

		float gravePriceTemp = 0.0;

		while (fscanf(file, "%s | %s | %f | %d - %d", &cemeteryOwnerTemp.username, &cemeteryOwnerTemp.password,
			&gravePriceTemp,
			&cemeterySizeTemp.rows, &cemeterySizeTemp.cols) != EOF)
		{
			cemeterySizeG = cemeterySizeTemp;
			gravePriceG = gravePriceTemp;
		}

		mainMenu(gravesList_file_path, list, cemeteryOwner_file_path);
	}
}

void mainMenu(const char* gravesList_file_path, t_List* list, const char* cemeteryOwner_file_path)
{
	int choice = 0;

	while (1)
	{
		printf("\n-----------------------");
		printf("\nCEMMY - cemetery system\n");
		printf("\nChoose option below:\n");
		printf("********************\n");
		printf("\n1) Add new deceased\n");
		printf("2) Show information about the deceased by personal number\n");
		printf("3) Cemetery owner menu\n");
		printf("4) Exit and save\n");
		printf("\nYour choice: ");
		scanf("%d", &choice);
		system("cls");

		switch (choice)
		{
		case 1:
		{
			t_Grave* grave = add_new_grave(*list, gravesList_file_path, cemeterySizeG, gravePriceG);
			if (grave != NULL)
			{
				insert_node_first(&list->head, *grave);
			}
			else
			{
				printf("This personal number already exists!\n");
			}
			break;
		}
		case 2:
		{
			char personalNum[PN_DATE_SIZE] = "";
			printf("\nEnter personal number: ");
			scanf("%s", &personalNum);

			t_Node* found = findPersonalNumber(list->head, personalNum);
			if (found == NULL)
			{
				printf("\nThe cemetery doesn't contain a person with the given personal number!\n");
			}
			else
			{
				printf("\nFirst name: %s", found->payload.person.firstName);
				printf("\nLast name: %s", found->payload.person.lastName);
				printf("\nPersonal number: %s", found->payload.person.personalNumber);
				printf("\nDeath date: %d/%d/%d", 
					found->payload.person.deathDate.day,
					found->payload.person.deathDate.month,
					found->payload.person.deathDate.year);
				printf("\nLocation: %d row - %d column\n",
					found->payload.location.row,
					found->payload.location.col);

				time_t nowTime = time(NULL);
				struct tm* tm = localtime(&nowTime);
				t_Date nowDate = { 0 };
				nowDate.day = tm->tm_mday;
				nowDate.month = tm->tm_mon + 1;
				nowDate.year = tm->tm_year + 1900;
				t_Date diff = calculateDiff(found->payload.person.deathDate, nowDate);
				int days = (diff.year * 365) + (diff.month * 30) + diff.day;

				if (days == 40)
				{
					printf("\n-------------------");
					printf("\n40 days after death\n");
					printf("-------------------\n\n");

				}
				else if (diff.month == 6 && diff.day == 0 && diff.year == 0)
				{
					printf("\n-------------------");
					printf("\n6 months after death\n");
					printf("-------------------\n\n");
				}
				else if (diff.year == 1 && diff.month == 0 && diff.day == 0)
				{
					printf("\n-------------------");
					printf("\n1 year after death\n");
					printf("-------------------\n\n");
				}
				else if (diff.year == 3 && diff.month == 0 && diff.day == 0)
				{
					printf("\n-------------------");
					printf("\n3 years after death\n");
					printf("-------------------\n\n");
				}

				char tempGraveStatus[PN_DATE_SIZE] = "";
				if (found->payload.paymentStatus == 0)
				{
					strcpy(tempGraveStatus, "reserved");
					printf("\nThe price of the grave is %.2f.", gravePriceG);
					printf("\nDo you want to buy the grave? (Yes/No) - ");
					char answer[4] = "";
					scanf("%s", &answer);

					if (compare_strings(answer, "Yes") == T)
					{
						found->payload.paymentStatus = 1;
						strcpy(tempGraveStatus, "purchased");
					}
				}
				else
				{
					strcpy(tempGraveStatus, "purchased");
				}
				printf("Grave status: %s", tempGraveStatus);
			}

			break;
		}
		case 3: cemeteryOwnerMenu(cemeteryOwner_file_path, gravesList_file_path, list);
			break;
		case 4: exit(7);
			break;
		
		default: printf("Invalid choice!");
			break;
		}
	}
}

void cemeteryOwnerMenu(const char* cemeteryOwner_file_path, const char* gravesList_file_path, t_List* list)
{
	FILE* fp = fopen(cemeteryOwner_file_path, "r");
	if (fp == NULL)
	{
		fp = createFile(cemeteryOwner_file_path);
	}
	if (fgetc(fp) == EOF)
	{
		printf("\nRegister cemetery owner");
		printf("\n****************************");
		registerCemeteryOwner(cemeteryOwner_file_path);
		showMenu(gravesList_file_path, cemeteryOwner_file_path, &list);

	}
	else
	{
		t_CemeteryOwner* cemeteryOwner = malloc((t_CemeteryOwner*)sizeof(t_CemeteryOwner));
		t_CemeteryOwner temp = { 0 };

		while (fscanf(fp, "%s | %s | %f | %d - %d", &temp.username, &temp.password, &temp.gravePrice,
			&temp.cemeterySize.rows, &temp.cemeterySize.cols) != EOF)
		{
			strcpy(cemeteryOwner->username, temp.username);
			strcpy(cemeteryOwner->password, temp.password);
			cemeteryOwner->gravePrice = temp.gravePrice;
			cemeteryOwner->cemeterySize.rows = temp.cemeterySize.rows;
			cemeteryOwner->cemeterySize.cols = temp.cemeterySize.cols;
		}

		cemeterySizeG.rows = cemeteryOwner->cemeterySize.rows;
		cemeterySizeG.cols = cemeteryOwner->cemeterySize.cols;
		gravePriceG = cemeteryOwner->gravePrice;

		eResult isSuccessfulLogin = login(cemeteryOwner);

		if (isSuccessfulLogin == valid)
		{
			system("cls");

			printf("\nSuccessful login!\n");

			int option = 0;
			int tempRows = 0;
			int tempCols = 0;

			while (1)
			{
				printf("\n\nChoose option below:\n");
				printf("********************\n");
				printf("\n1) Change cemetery size\n");
				printf("2) Change price per grave\n");
				printf("3) Print all graves records\n");
				printf("4) Main menu\n");
				printf("5) Exit and save\n");
				printf("\nYour choice: ");
				scanf("%d", &option);
				system("cls");
				switch (option)
				{
				case 1: // Change cemetery size
					printf("\nRows: ");
					scanf("%d", &tempRows);
					printf("Columns: ");
					scanf("%d", &tempCols);
					if (tempCols < cemeterySizeG.cols || tempRows < cemeterySizeG.rows)
					{
						printf("\nOnly enlargement of the territory is allowed!\n");
						break;
					}
					cemeteryOwner->cemeterySize.rows = tempRows;
					cemeteryOwner->cemeterySize.cols = tempCols;
					cemeterySizeG.rows = cemeteryOwner->cemeterySize.rows;
					cemeterySizeG.cols = cemeteryOwner->cemeterySize.cols;
					break;

				case 2: // Change price per grave
					printf("\nEnter new price per grave: ");
					scanf("%f", &cemeteryOwner->gravePrice);
					gravePriceG = cemeteryOwner->gravePrice;
					break;

				case 3: //Print all graves info
					print_list(list);
					break;

				case 4: 
					mainMenu(gravesList_file_path, list, cemeteryOwner_file_path);
					break;
				case 5:
					exit(7);
					break;
				default: printf("Invalid choice!");
					break;
				}

				FILE* fp = fopen(cemeteryOwner_file_path, "w");
				eResult result = checkNullFile(&fp);
				if (result == valid)
				{
					fprintf(fp, " %s | %s | %.2f | %d - %d",
						cemeteryOwner->username, cemeteryOwner->password,
						cemeteryOwner->gravePrice,
						cemeteryOwner->cemeterySize.rows, cemeteryOwner->cemeterySize.cols);

					fclose(fp);
				}
			}
		}
	}
}


eResult login(t_CemeteryOwner* cemeteryOwner)
{
	eResult result = invalid;
	boolean areEqual = F;
	char tempString[20];

	printf("\nLog in");
	printf("\n*****************");

	while (result != valid)
	{
		printf("\nUsername: ");
		scanf("%s", &tempString);
		areEqual = compare_strings(tempString, cemeteryOwner->username);
		if (areEqual == T)
		{
			printf("Password: ");
			scanf("%s", &tempString);
			areEqual = compare_strings(tempString, cemeteryOwner->password);
			if (areEqual == T)
			{
				result = valid;
			}
			else
			{
				while (areEqual != T)
				{
					printf("\nIncorrect password!\n");

					printf("Forgotten password? (Yes/No) - ");
					scanf("%s", &tempString);

					areEqual = compare_strings(tempString, "Yes");
					if (areEqual == T)
					{
						printf("Sorry, try again when you remember the password. :)\n");
						return invalid;
					}
					else
					{
						printf("\nPassword: ");
						scanf("%s", &tempString);
						areEqual = compare_strings(tempString, cemeteryOwner->password);
						result = valid;
					}

				}
			}
		}
		else
		{
			printf("\nIncorrect username!\n");
			printf("\nHave you forgotten your username? (Yes/No) - ");
			scanf("%s", &tempString);
			areEqual = compare_strings(tempString, "Yes");
			if (areEqual == T)
			{
				printf("Sorry, try again when you remember your username. :)\n");
				return invalid;
			}
			else
			{
				result = invalid;
			}
		}
	}

	return result;
}