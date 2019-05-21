// Only using ENTAB for the purpose of this exercise.

#include <stdio.h>
#include <ctype.h>
// #include <stdlib.h>

#define MAXLENGTH 4096
#define TABLENGTH 2

int get_line(char line[], int limit);
int get_line_length(char line[]);
void copy_untabbed_to_tabbed(char untabbed[], char tabbed[], int start_column, int column_interval);
int column_num_in_tab_list(int col_num);

int tab_list[MAXLENGTH];
int tab_list_length = 0;

int main(int argc, char *argv[])
{
  int length;
  char untabbed[MAXLENGTH];
  char tabbed[MAXLENGTH];

  int start_col = 0;
  int col_interval = 1;
  int c;

  while(--argc > 0 && isdigit(c = *(++argv)[0])) {
    tab_list[tab_list_length++] = c - '0';
  }

  while ((length = get_line(untabbed, MAXLENGTH)) > 0)
  {
    copy_untabbed_to_tabbed(untabbed, tabbed, start_col, col_interval);
    printf("%s", tabbed);
  }

  return 0;
}

int get_line(char line[], int limit)
{
  int c, count;
  count = 0;
  while ((c = getchar()) != EOF && c != '\n' && count < limit - 1)
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

int get_line_length(char line[])
{
  int count = 0;
  while (line[count] != '\0')
  {
    count++;
  }

  return count;
}

void copy_untabbed_to_tabbed(char untabbed[], char tabbed[], int start_col, int col_interval)
{
  int num_tabs, num_spaces;
  int u = 0;
  int t = 0;
  int space_count = 0;
  int col_count = 1;

  int l = get_line_length(untabbed);
  while (u < l)
  {
    if (untabbed[u] != ' ')
    {
      tabbed[t++] = untabbed[u++];
    } else if (column_num_in_tab_list(col_count++)){
      while (untabbed[u] == ' ')
      {
        space_count++;
        u++;
      }

      num_spaces = space_count % TABLENGTH;
      num_tabs = (space_count - num_spaces) / TABLENGTH;

      for (int i = 0; i < num_tabs; i++)
      {
        tabbed[t] = '\t';
        t++;
      }
      for (int i = 0; i < num_spaces; i++)
      {
        tabbed[t] = ' ';
        t++;
      }

      space_count = 0;
    }
    else
    {
      while (untabbed[u] == ' ')
      {
        tabbed[t++] = untabbed[u++];
      }
    }
  }

  tabbed[t] = '\0';
}

int column_num_in_tab_list(int col_num) {
  for (int i = 0; i < tab_list_length; i++) {
    if (tab_list[i] == col_num) {
      return 1;
    }
  }
  return 0;
}
