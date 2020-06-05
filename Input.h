#pragma once

#include "Header.h"

t_Grave* add_new_grave(t_List list, const char* gravesList_file_path, t_CemeterySize cemSize, float gravePrice);
boolean isLocationFree(t_Location* location, t_Node* p_head);
void addGravePrice(t_CemeteryOwner* cemeteryOwner);
void registerCemeteryOwner(const char* file_path);
t_Node* findPersonalNumber(t_Node* p_head, const char* personalNumber);




