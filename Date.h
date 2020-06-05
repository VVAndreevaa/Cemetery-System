#pragma once
#include<stdio.h>
#include "Header.h"

// calculate the difference of two dates in years, months and days
t_Date calculateDiff(const t_Date date0, const t_Date date1);

// check whether year is a leap year
eIsLeap is_leap_year(const t_Date date);

t_Date add_date(const char* dateOfType);