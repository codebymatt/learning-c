#include <stdio.h>
#include <ctype.h>
#include <string.h>

int getword(char *word, int lim)
{
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  if (c == '\n')
  {
    *w++ = c;
    *w = '\0';
    return w[0];
  }

  if (isspace(c = getch()))
  {
    *w++ = c;
    *w = '\0';
    return w[0];
  }

  if (c != EOF)
  {
    // SKIP PREPROCESSOR CONTROL LINES
    // OK to skip lines starting with '#', as only time it's
    // used outside '#define' is inside string constant.
    if (c == '#')
    {
      *w++ = c;
      while (isalnum(c = getch()))
      {
        *w++ = c;
      }
      if (!isspace(c)) {
        ungetch(c);
      }
      *w = '\0';
      return w[0];
    }
    // SKIP COMMENT LINES
    if (c == '/')
    {
      if ((c = getch()) == '/')
      {
        while ((c = getch()) != '\n')
        {
          ;
        }
      }
      else
      {
        ungetch(c);
        *w++ = '/';
        *w = '\0';
        return w[0];
      }
    }
    else
    {
      *w++ = c;
    }
  }

  // STRING CONSTANTS
  if (c == '"')
  {
    for (; --lim > 0; w++)
    {
      if ((*w = getch()) == '"')
      {
        w++;
        break;
      }
    }
  }

  if (c == '\'')
  {
    for (; --lim > 0; w++)
    {
      if ((*w = getch()) == '\'')
      {
        w++;
        break;
      }
    }
  }

  // NORMAL WORDS
  if (!isalnum(c))
  {
    *w = '\0';
    return c;
  }

  for (; --lim > 0; w++)
  {
    if (!isalnum(*w = getch()) && (*w != '_'))
    {
      ungetch(*w);
      break;
    }
  }
  *w = '\0';
  return word[0];
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