#include <stdio.h>
#include "GravesList.h"
#include "File.h"
#include "Input.h"
#include "Output.h"

int main()
{
	t_List list = initialize_list();
	showMenu("gravesList.txt", "COList.txt", &list);
	writeInFile("gravesList.txt", &list);
	clear_list(&list);
	return 0;
}