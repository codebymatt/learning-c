// Extend entab and detab to accept the shorthand 'entab -m +n to mean tab stops every n columns,
// starting at column m. Choose convenient default behaviour for the user.

// In an ideal world where I wanted to be a purist the array handling here would use pointers.
// This is not an ideal world, and I stopped being a purist (when it comes to these exercises
// at least) long ago.

#include <stdio.h>
#define MAXLENGTH 4096

// Tabs in my editor are currently taking up 2 spaces, so that shall be their
// replacement value in this program.
#define TABLENGTH 2

// I've also chosen not to modify the array in place, but to create a new array
// and copy the characters over (with tabs replaced as required)

void replace_tabs_with_spaces(char old[], char new[], int start_col, int col_interval);
int get_line(char line[], int limit);

int main(int argc, char *argv[])
{
  int length;
  char tabbed_line[MAXLENGTH];
  char spaced_line[MAXLENGTH];

  int start_col = 0;
  int col_interval = 1;
  int c;

  while (--argc > 0 && *(++argv)[0] == '-')
  {
    while ((c = (++(*argv))[0]) != 0)
    {
      switch (c)
      {
      case ('m'):
        start_col = *(++argv)[0] - '0';
        --argc;
        break;
      case ('n'):
        col_interval = *(++argv)[0] - '0';
        --argc;
        break;
      default:
        printf("Hitting here: default\n");
        break;
      }
    }
  }

  while ((length = get_line(tabbed_line, MAXLENGTH)) > 0)
  {
    replace_tabs_with_spaces(tabbed_line, spaced_line, start_col, col_interval);
    printf("%s", spaced_line);
  }

  return 0;
}

int get_line(char line[], int limit)
{
  int c, count;
  count = 0;

  while ((c = getchar()) != EOF && c != '\n' && count < limit - 2)
  {
    line[count] = c;
    count++;
  }

  if (c == '\n')
  {
    line[count] = c;
    count++;
  }

  line[count] = '\0';

  return count;
}

void replace_tabs_with_spaces(char tabbed[], char spaced[], int start_col, int col_interval)
{
  int t = 0;
  int s = 0;
  int col_count = 0;

  while (tabbed[t] != '\0')
  {
    if (tabbed[t] != '\t')
    {
      spaced[s++] = tabbed[t++];
    }
    else if ((col_count++ == start_col) ||
             ((col_count > start_col) && (((col_count - 1) - start_col) % col_interval == 0)))
    {
      for (int i = 0; i < TABLENGTH; i++)
      {
        spaced[s + i] = ' ';
      }

      s += TABLENGTH;
      t++;
    }
    else
    {
      spaced[s++] = tabbed[t++];
    }
  }

  spaced[s] = '\0';
}
