#include <stdio.h>
#include <ctype.h>
#include <string.h>

int getword_2(char *word, int lim, int *linenum)
{
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch()))
  {
    if (c == '\n')
    {
      (*linenum)++;
    }
  }

  if (c != EOF)
  {
    // SKIP PREPROCESSOR CONTROL LINES
    // OK to skip lines starting with '#', as only time it's
    // used outside '#define' is inside string constant.
    if (c == '#')
    {
      while ((c = getch()) != '\n')
      {
        ;
      }
      if (c == '\n')
      {
        (*linenum)++;
      }
      *w = '\0';
      return w[0];
    }
    // SKIP COMMENT LINES
    else if (c == '/')
    {
      if ((c = getch()) == '/')
      {
        while ((c = getch()) != '\n')
        {
          ;
        }
        if ((c = getch()) != EOF)
        {
          *w++ = c;
          if (c == '\n')
          {
            (*linenum)++;
          }
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
  if (!isalpha(c))
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