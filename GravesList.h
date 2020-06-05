#pragma once

#include "Header.h"

t_List initialize_list();
boolean remove_grave_by_personalNumber(t_Node** p_head, const char* personalNumber);
boolean compare_strings(const char* first_string, const char* second_string);
void print_list(t_List* list);
void clear_list(t_List* list);
void insert_node_first(t_Node** p_head, const t_Grave grave);
