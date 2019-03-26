#include <stdio.h>
#include <ctype.h>

int getch(void);
int ungetch(int);
double getfloat(double *);

int main() {}

double getfloat(double *pn)
{
  int c, sign;

  while (isspace(c = getch()))
    ;

  if (!isdigit(c) && c != EOF && c != '+' && c != '-')
  {
    ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
  {
    int next = getch();
    if (isdigit(next))
    {
      c = next;
    }
    else
    {
      ungetch(next);
      ungetch(c);
      return 0.0;
    }
  }

  int tracking_decimals = 0;
  int decimal_count = 0;

  for (*pn = 0.0; isdigit(c) || c == '.'; c = getch())
  {
    if (c == '.')
    {
      tracking_decimals = 1;
    }
    else
    {
      if (tracking_decimals)
      {
        decimal_count++;
      }
      *pn = (10 * *pn) + (c - '0');
    }
  }

  while (decimal_count > 0)
  {
    *pn /= 10;
    decimal_count--;
  }

  *pn *= sign;
  if (c != EOF)
  {
    ungetch(c);
  }

  return c;
}

int getch(void) {}
int ungetch(int i) {}