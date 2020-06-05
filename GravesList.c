#include<stdlib.h>
#include "GravesList.h"

t_List initialize_list()
{
	t_List list;
	list.head = NULL;
	return list;
}

void insert_node_first(t_Node** p_head, const t_Grave grave)
{
	t_Node* new_node = (t_Node*)malloc(sizeof(t_Node));
	if (new_node != NULL)
	{
		new_node->payload = grave;
		new_node->next = *p_head;

		*p_head = new_node;
	}
	else
	{
		printf("Memory was not allocated correctly!");
	}
	new_node = NULL;
	free(new_node);
}

void clear_list(t_List* list)
{
	t_Node* temp = list->head;

	while (temp != NULL)
	{
		t_Node* free_node = temp;
		temp = temp->next;

		free(free_node);
	}

	list->head = NULL;
}


void print_list(t_List* list)
{
	t_Node* node = NULL;

	if (list->head == NULL)
	{
		printf("\nThe cemetery is empty!\n");
	}
	else
	{
		printf("\nThe cemetery contains:\n");
		for (node = list->head; node != NULL; node = node->next)
		{
			printf("\nFirst name: %s", node->payload.person.firstName);
			printf("\nLast name: %s", node->payload.person.lastName);
			printf("\nPersonal number: %s", node->payload.person.personalNumber);
			printf("\nDeath date: %d/%d/%d", 
				node->payload.person.deathDate.day,
				node->payload.person.deathDate.month,
				node->payload.person.deathDate.year);
			printf("\nLocation: %d row - %d column", 
				node->payload.location.row,
				node->payload.location.col);
			printf("\nGrave price: %.2f", node->payload.price);

			char tempGraveStatus[PN_DATE_SIZE] = "";
			if (node->payload.paymentStatus == 0)
			{
				strcpy(tempGraveStatus, "reserved");
			}
			else
			{
				strcpy(tempGraveStatus, "purchased");
			}
			printf("\nGrave status: %s", tempGraveStatus);
			printf("\n-------------------------------------");
		}
	}
}

boolean compare_strings(const char* first_string, const char* second_string)
{
	while (*first_string == *second_string)
	{
		if (*first_string == '\0' || *second_string == '\0')
		{
			break;
		}
		first_string++;
		second_string++;
	}
	if (*first_string == '\0' && *second_string == '\0')
	{
		return T;
	}
	else
	{
		return F;
	}
}