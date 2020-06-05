#pragma once

#include "Header.h"

eResult login(t_CemeteryOwner* cemeteryOwner);
void cemeteryOwnerMenu(const char* cemeteryOwner_file_path, const char* gravesList_file_path, t_List* list);
void showMenu(const char* gravesList_file_path, const char* cemeteryOwner_file_path, t_List* list);
void mainMenu(const char* gravesList_file_path, t_List* list);
