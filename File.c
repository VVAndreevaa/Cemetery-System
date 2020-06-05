#include<stdio.h>
#include<stdlib.h>
#include "File.h"

FILE* createFile(const char* file_path)
{
	FILE* fp = fopen(file_path, "w+");
	eResult result = checkNullFile(&fp);
	if (result != valid)
	{
		return NULL;
	}
	fclose(fp);
	return &fp;
}

eResult checkNullFile(const FILE* fp)
{
	eResult result = invalid;
	if (fp == NULL)
	{
		printf("Error: No such file or directory!");
		result = invalid;
	}
	else
	{
		result = valid;
	}

	return result;
}

eResult writeInFile(const char* file_path, t_List* list)
{
	t_Node* node = NULL;
	eResult result = invalid;

	FILE* fp = fopen(file_path, "a");

	result = checkNullFile(&fp);

	if (result == valid)
	{
		for (node = list->head; node != NULL; node = node->next)
		{
			fprintf(fp, "%d/%d/%d | %s | %s | %s | %d | %d | %f | %d | %s",
				node->payload.person.deathDate.day,
				node->payload.person.deathDate.month,
				node->payload.person.deathDate.year,

				node->payload.person.personalNumber,
				node->payload.person.firstName,
				node->payload.person.lastName,

				node->payload.location.row,
				node->payload.location.col,

				node->payload.price,
				node->payload.paymentStatus,
				node->payload.endDate);
		}
	}
	else
	{
		result = invalid;
	}



	return result;
}

void addDataToList(const char* file_path, t_List* list)
{
	t_Grave temp = { 0 };

	FILE* fp = fopen(file_path, "r");

	if (fp != NULL)
	{
		t_Node* new_node = NULL;

		for (; fscanf(fp, "%d/%d/%d | %s | %s | %s | %d-%d | %f | %d | %s\n",
			&temp.person.deathDate.day,
			&temp.person.deathDate.month,
			&temp.person.deathDate.year,

			&temp.person.personalNumber,
			&temp.person.firstName,
			&temp.person.lastName,

			&temp.location.row,
			&temp.location.col,

			&temp.price,
			&temp.paymentStatus,
			&temp.endDate) != EOF;

		new_node->next = list->head, list->head = new_node)
		{
			new_node = (t_Node*)malloc(sizeof(t_Node));

			if (new_node == NULL)
			{
				printf("Memory allocation failed!\n");
			}
			else
			{
				new_node->payload = temp;
			}
		}
		fclose(fp);
	}
	else
	{
		createFile(file_path);
	}
}