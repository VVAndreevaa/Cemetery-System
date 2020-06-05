#pragma once

#include<stdio.h>
#include "Header.h"


FILE* createFile(const char* file_path);
eResult checkNullFile(const FILE* fp);
eResult writeInFile(const char* file_path, t_List* list);
void addDataToList(char* file_path, t_List* list);

