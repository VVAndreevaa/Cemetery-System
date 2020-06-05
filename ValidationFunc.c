#include<stdio.h>
#include "ValidationFunc.h"
#include "Date.h"

eResult validate_date(t_Date date)
{
	eResult isValid = valid;
	eIsLeap isLeap = normal;

	if (date.year >= 1753 && date.year <= 9998)
	{
		isLeap = is_leap_year(date);

		// check whether month is between 1 and 12
		if (date.month >= 1 && date.month <= 12)
		{
			// check for days in feb
			if (date.month == 2)
			{
				if (isLeap && date.day == 29)
				{
					isValid = valid;
				}
				else if (date.day > 28)
				{
					isValid = invalid;
				}
			}

			// check for days in April, June, September and November
			else if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)
			{
				if (date.day > 30)
				{
					isValid = invalid;
				}
			}

			// check for days in rest of the months 
			// i.e Jan, Mar, May, July, Aug, Oct, Dec
			else if (date.day > 31)
			{
				isValid = invalid;
			}
		}
		else
		{
			isValid = invalid;
		}
	}
	else
	{
		isValid = invalid;
	}

	return isValid;
}