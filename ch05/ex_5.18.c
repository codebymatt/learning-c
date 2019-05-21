// Doesn't handle invalid declarations: make it recover from input errors,
// Taking 'handling error' to mean recovering from missing bracket or parentheses while still
// making an educated guess at the declaration, and returning the declaration without a NAME
// if it's not present.

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

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main()
{
  while (gettoken() != EOF)
  {
    strcpy(datatype, token);
    out[0] = '\0';
    name[0] = '\0';
    dcl();
    if (tokentype != '\n')
    {
      printf("syntax error\n");
    }
    if (name[0] != '\0')
    {
      printf("%s: %s %s\n\n", name, out, datatype);
    }
    else
    {
      printf("Unspecified name: %s %s\n\n", out, datatype);
    }
  }
}

void dcl(void)
{
  int ns;

  for (ns = 0; gettoken() == '*';)
  {
    ns++;
  }
  dirdcl();
  while (ns-- > 0)
  {
    strcat(out, " pointer to");
  }
}

void dirdcl(void)
{
  int type;

  if (tokentype == '(')
  {
    dcl();
    if (tokentype != ')')
    {
      printf("error: missing ). Adding one in, this may change the results\n");
      tokentype = ')';
    }
  }
  else if (tokentype == NAME)
  {
    strcpy(name, token);
  }
  else
  {
    printf("error: expected name or (dcl)\n");
  }

  while ((type = gettoken()) == PARENS || type == BRACKETS)
  {
    if (type == PARENS)
    {
      strcat(out, " function returning");
    }
    else
    {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}

int gettoken(void)
{
  int c, getch(void);
  void ungetch(int);
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
      *p++ = ']';
    }
    else
    {
      *p++ = ']';
    }
    // if (*p == '\n')
    // p++;
    // SOMETHING IS MESSY HERE
    // if (*p != ']')
    // {
    //   ungetch(']');
    //   printf("Missing ']', inserting one. This may change results\n");
    // }
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

// char buffer;
// int buffer_empty = 0;

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