#include <stdio.h>

void strcpy_n(char *s, char *t, int n)
{
  int counter = 0;
  while ((counter++ < n) && (*s++ = *t++) != '\0')
  {
    ;
  }
  *s = '\0';
}

void strncat_n(char *s, char *t, int n)
{
  while (*s != '\0')
  {
    s++;
  }

  int counter = 0;
  while ((counter++ < n) && (*t != '\0'))
  {
    *s++ = *t++;
  }
  *s = '\0';
}

int strncmp_n(char *s, char *t, int n)
{
  int counter = 0;
  // Decrement n by 1 since the subtraction always happens AFTER the loop
  // (i.e when n == counter)
  for (; (counter++ < n - 1) && *s == *t; s++, t++)
  {
    if (*s == '\0')
    {
      return 0;
    }
    // counter++;
  }
  return *s - *t;
}

// Simple test for strncmp_n
int main()
{
  char first[100];
  char second[100];
  scanf("%s", first);
  scanf("%s", second);

  printf("%d\n", strncmp_n(first, second, 3));
}