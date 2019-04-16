
#include <stdio.h>
#include <ctype.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day)
{
  if (!isdigit(year) || year < 0)
  {
    printf("Invalid year: it must be a positive integer\n");
  }
  else if (!isdigit(month) || month < 1 || month > 12)
  {
    printf("Invalid month: it must be a positive integer between 1 and 12 (inclusive)\n");
  }

  int i, leap;

  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

  if (!isdigit(day) || day < 1 || day > daytab[leap][month])
  {
    printf("Invalid day: it must be a positive integer between 1 and the end \
            of the month you're using (inclusive)\n");
  }

  for (i = 1; i < month; i++)
  {
    day += daytab[leap][i];
  }
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
  if (!isdigit(year) || year < 0)
  {
    printf("Invalid year: it must be a positive integer\n");
  }

  int i, leap;

  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

  if (!isdigit(yearday) || yearday < 0 || (leap && yearday > 366) || yearday > 365)
  {
    printf("Invalid yearday: it must be an positive integer between 1 and 366 (inclusive)\n");
  }

  for (i = 1; yearday > daytab[leap][i]; i++)
  {
    yearday -= daytab[leap][i];
  }
  *pmonth = i;
  *pday = yearday;
}

int main()
{
  // For compilation purposes
}