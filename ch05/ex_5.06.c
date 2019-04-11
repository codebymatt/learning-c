#include <stdio.h>
#include <string.h>

#define MAX 1024

int atoi(char s[]);
void reverse(char s[]);

int main()
{
  char array[MAX];
  int converted_num;
  scanf("%s", array);

  converted_num = atoi(array);
  reverse(array);

  printf("Converted integer is: %d\n", converted_num);
  printf("Reversed input is: %s\n", array);
}

int atoi(char s[])
{
  int i, n;

  n = 0;
  while (*s >= '0' && *s <= '9')
  {
    n = 10 * n + (*s - '0');
    ++s;
  }
  return n;
}

void reverse(char s[])
{
  int c, i, j;
  char *t;
  t = &s[strlen(s) - 1];

  while (s < t)
  {
    c = *s;
    *s = *t;
    *t = c;

    s++;
    t--;
  }
}