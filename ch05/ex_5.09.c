#include <stdio.h>
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day)
{
  int i, leap;

  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
  for (i = 1; i < month; i++)
  {
    day += *(daytab[leap] + i);
  }

  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;

  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
  for (i = 1; yearday > *(daytab[leap] + i); i++)
  {
    yearday -= *(daytab[leap] + i);
  }
  *pmonth = i;
  *pday = yearday;
}

int main()
{
  int year = 2019;
  int month = 4;
  int day = 10;
  int calculated_day = day_of_year(year, month, day);
  printf("Day is: %d\n", calculated_day);

  int reversed_month, reversed_day;

  month_day(year, calculated_day, &reversed_month, &reversed_day);
  printf("Month is: %d    Day is: %d\n", reversed_month, reversed_day);

  return 0;
}
