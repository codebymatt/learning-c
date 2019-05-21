// Redundant parentheses happen when an expression being pointed to is unnecessarily wrapped
// in them.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum
{
  NAME,
  PARENS,
  BRACKETS
};

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char out[1000];

void ungetch(int);

int main()
{
  int type;
  char temp[MAXTOKEN];

  while (gettoken() != EOF)
  {
    strcpy(out, token);
    while((type = gettoken()) != '\n') {
      if (type == PARENS || type == BRACKETS) {
        strcat(out, token);
      } else if (type == '*') {
        if ((type = gettoken()) == '*') {
          sprintf(temp, "*%s", out);
          ungetch(type);
        } else {
          ungetch(type);
          sprintf(temp, "(*%s)", out);
        }
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else {
        printf("invalid input at %s\n", token);
      }
    }
    printf("%s\n", out);
  }
  return 0;
}

int gettoken(void)
{
  int c, getch(void);
  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
  {
    ;
  }

  if (c == '(')
  {
    if ((c = getch()) == ')')
    {
      strcpy(token, "()");
      return tokentype = PARENS;
    }
    else
    {
      ungetch(c);
      return tokentype = '(';
    }
  }
  else if (c == '[')
  {
    char temp;
    for (*p++ = c; (temp = getch()) != ']' && temp != '\n';)
    {
      *p++ = temp;
    }
    if (temp == '\n')
    {
      ungetch(temp);
      printf("Missing ']', inserting one. This may change results\n");
    }
      *p++ = ']';
    *p = '\0';
    return tokentype = BRACKETS;
  }
  else if (isalpha(c))
  {
    for (*p++ = c; isalnum(c = getch());)
    {
      *p++ = c;
    }
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  }
  else
  {
    return tokentype = c;
  }
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= BUFSIZE)
  {
    printf("ungetch: too many characters\n");
  }
  else
  {
    buf[bufp++] = c;
  }
}