#include<string.h>
#include<stdlib.h>
#include<string.h>
#include "Date.h"
#include "ValidationFunc.h"

t_Date calculateDiff(const t_Date date0, const t_Date date1)
{
	t_Date diff = { 0 };
	t_Date temp = { 0 };

	temp.day = date1.day;
	temp.month = date1.month;
	temp.year = date1.year;

	if (validate_date(date0) == invalid)
	{
		printf("First date is invalid!");
	}
	if (validate_date(date1) == invalid)
	{
		printf("Second date is invalid!");
	}
	if (date1.day < date0.day)
	{
		// borrow days from february
		if (date1.month == 3)
		{
			// check whether year is a leap year
			if (is_leap_year(date1) == normal)
			{
				temp.day += 29;
			}
			else if (is_leap_year(date1) == leap)
			{
				temp.day += 28;
			}
		}
		// borrow days from April or June or September or November
		else if (temp.month == 5 || temp.month == 7 || temp.month == 10 || temp.month == 12)
		{
			temp.day += 30;
		}
		// borrow days from Jan or Mar or May or July or Aug or Oct or Dec
		else
		{
			temp.day += 31;
		}

		temp.month -= 1;
	}
	if (date1.month < date0.month)
	{
		temp.month += 12;
		temp.year -= 1;
	}

	diff.day = temp.day - date0.day;
	diff.month = temp.month - date0.month;
	diff.year = temp.year - date0.year;

	return diff;
}


eIsLeap is_leap_year(t_Date date)
{
	eIsLeap result = normal;
	if ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0))
	{
		result = leap;
	}
	return result;
}


t_Date add_date(const char* dateOfType) // convertDateStringToInts and add date
{
	char tempStringDate[PN_DATE_SIZE] = "";
	eResult result = invalid;
	char* delim = "/";
	t_Date tempDate = { 0 };
	char string[11];

	while (result != valid)
	{
		printf("\n%s (dd/mm/yyyy): ", dateOfType);
		scanf("%s", &tempStringDate);

		if (strlen(tempStringDate) != 10)
		{
			printf("Please enter date in format \"dd/mm/yyyy\"");
			result = invalid;
			continue;
		}

		strcpy(string, tempStringDate);

		tempDate.day = atoi(strtok(string, delim));
		tempDate.month = atoi(strtok(NULL, delim));
		tempDate.year = atoi(strtok(NULL, delim));

		result = validate_date(tempDate);
		if (result == invalid)
		{
			printf("\nInvalid date! Please enter a valid date.\n");
		}
	}
	return tempDate;
}
