// Disregarding check to see how much faster new implementation of read line is.
// Also haven't tested this in context, just ensured it compiles.

#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

// container array must have length >= MAXLEN
int readlines(char lines[][MAXLEN], int maxlines)
{
  int len, nlines;
  nlines = 0;

  // char *p = lines;
  char line[MAXLEN];

  size_t buf_size = MAXLEN;

  nlines = 0;
  while ((len = getline((char **)&lines[nlines], &buf_size, stdin)) > 0)
  {
    if (nlines >= maxlines)
    {
      return -1;
    }
    else
    {
      lines[nlines++][len - 1] = '\0';
    }
  }
  return nlines;
}

int main()
{
  return 0;
}