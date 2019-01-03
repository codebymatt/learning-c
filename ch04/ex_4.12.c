#include <stdio.h>
#include <string.h>

#define MAXCHAR 32

void int_to_a(int, char [], int index);

int main()
{
  int i;
  char s[MAXCHAR];

  scanf("%d", &i);
  int_to_a(i, s, 0);

  int len = strlen(s);
  if (i < 0) {
    s[len++] = '-';
  }

  for(int i = 0, j = len-1; i < len/2; i++, j--) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
  }

  printf("%s\n", s);
  return 0;
}

void int_to_a(int i, char s[], int index)
{
  if (i < 0) {
    i *= -1;
  }

  if (i > 10) {
    int_to_a(i / 10, s, index + 1);
  }
  
  s[index] = (i % 10) + '0';
}