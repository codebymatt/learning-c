#include <stdio.h>

void my_strcat(char *s, char *t)
{
  while(*s != '\0') {
    s++;
  }

  while (*t != '\0')
  {
    *s++ = *t++;
  }

  *s = '\0';
}

int main()
{
  int MAX_SIZE = 100;
  char first[MAX_SIZE];
  char second[MAX_SIZE];
  scanf("%s", first);
  scanf("%s", second);

  my_strcat(first, second);

  printf("%s\n", first);
  return 0;
}