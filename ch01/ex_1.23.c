#include <stdio.h>
#define MAXLENGTH 4096

/* Assume program compiles correctly */

int read_line(char line[], int lim);
int print_line_without_comments(char original[], int in_comment);
int get_line_length(char line[]);

int main()
{
  int len, c, in_comment;
  char line[MAXLENGTH];
  in_comment = 0;

  while ((len = read_line(line, MAXLENGTH)) > 0)
  {
    in_comment = print_line_without_comments(line, in_comment);
  }
  return 0;
}

int read_line(char line[], int lim)
{
  int c, count;
  count = 0;

  while ((c = getchar()) != EOF && c != '\n' && count < lim - 1)
  {
    line[count++] = c;
  }

  if (c == '\n')
  {
    line[count++] = c;
  }

  line[count] = '\0';
  return count;
}

int print_line_without_comments(char line[], int in_comment)
{
  int len = get_line_length(line);
  int in_quote = 0;
  char copy[MAXLENGTH];
  int o, c;
  c = 0;
  o = 0;

  while (o < len)
  {
    if (!in_comment && !in_quote && line[o] == '"')
    {
      in_quote = 1;
      o++;
    }
    else if (
        !in_comment &&
        in_quote &&
        line[o - 1] != '\\' &&
        line[o] == '"')
    {
      in_quote = 0;
      o++;
    }

    if (!in_quote && !in_comment && line[o] == '/' && line[o + 1] == '*')
    {
      in_comment = 1;
      o++;
    }
    else if (!in_quote && in_comment && line[o] == '*' && line[o + 1] == '/')
    {
      in_comment = 0;
      o = o + 2;
    }
    else if (in_comment)
    {
      o++;
    }

    if (!in_comment)
    {
      copy[c++] = line[o++];
    }
  }

  copy[c] = '\0';
  printf("%s", copy);

  return in_comment;
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
