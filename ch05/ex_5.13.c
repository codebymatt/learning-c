// Write the program tail, which prints the last n lines of its input. By default, n is 10, say,
// but it can be changed by an optional argument, so that tail -n prints the last n lines. The
// program should behave rationally no matter how unreasonable the input or the value of n. Write
// the program so it makes the best use of available storage; lines should be stored as in the
// sorting program of Section 5.6, not in a two-dimensional array of fixed size.

// Assume input is single digit. Could handle aribrarily sized input, but would have to convert a
// character array to int, and I'm choosing not to do that.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 1024
#define LINELENGTH 4096

int readlines(char *line_ptr[], int maxlines, unsigned long *line_length);

int main(int argc, char *argv[])
{
  char *lines[MAXLINES];
  int line_count;
  unsigned long line_length = LINELENGTH;
  int lines_to_print = 10;
  int c;

  while (--argc > 0 && (*(++argv)[0] == '-'))
  {
    c = (++(*argv))[0];

    switch (c)
    {
    case 'n':
      if (argc > 1)
      {
        lines_to_print = (*(++argv))[0] - '0';
        argc--;
        break;
      }
      else
      {
        printf("Must supply argument when specifying 'n'\n");
        break;
      }
    default:
      break;
    }
  }

  line_count = readlines(lines, MAXLINES, &line_length);

  if (line_count == -1)
  {
    printf("Could not read input properly\n");
    return 1;
  }

  if (lines_to_print > line_count)
  {
    lines_to_print = line_count;
  }
  printf("LINES TO PRINT: %d\n", lines_to_print);

  while (lines_to_print > 0)
  {
    printf("%s\n", lines[line_count - (lines_to_print--)]);
  }

  return 0;
}

int readlines(char *line_ptr[], int maxlines, unsigned long *line_length)
{
  int len, nlines;
  char *p, *line[LINELENGTH];

  nlines = 0;
  while ((len = getline(&(line[0]), line_length, stdin)) > 0)
  {
    if (nlines > maxlines || (p = malloc(len)) == NULL)
    {
      return -1;
    }
    else
    {
      (*line)[len - 1] = '\0';
      strcpy(p, *line);
      line_ptr[nlines++] = p;
    }
  }
  return nlines;
}