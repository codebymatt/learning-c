#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'

int sign = 1.0;

static int buffer = '\0';

int getch(void);
int main() {}

int getop(char s[])
{
  sign = 1.0;
  int i, c, next;

  while((s[0] = c = getch()) == ' ' || c == '\t') {
    ;
  }

  s[1] = '\0';

  i = 0;
  if (!isdigit(c) && c != '.') {

    if (c == '-') {
      if (isdigit(next = getch())) {
        c = next;
        s[i++] = c;
        sign = -1.0;
      } else {
        return c;
      }
    } else {
      return c;
    }
  }

  if (isdigit(c)) {
    while(isdigit(s[++i] = c = getch())) {
      ;
    }
  }

  if (c == '.') {
    while (isdigit(s[++i] = c = getch())) {
      ;
    }
  }
  
  s[i] = '\0';
  if (c != EOF) {
    buffer = c;
  }
  return NUMBER;
}

int getch(void)
{
  if (buffer == '\0') {
    return getchar();
  } else {
    int temp = buffer;
    buffer = '\0';
    return temp;
  }
}