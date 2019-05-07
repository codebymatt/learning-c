#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define LINELENGTH 4096
char *lineptr[MAXLINES];

int my_getline(char s[], int lim);
int readlines(char *lineptr[], int nlines, int line_length);
void writelines(char *lineptr[], int nlines);

void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *, int, int, int), int reversed, int fold, int directory);
int numcmp(char *, char *, int, int);
int my_strcmp(const void *, const void *, int, int, int);
void strlwr(char[]);
int dircmp(const void *, const void *);
void collapse(char[]);

int main(int argc, char *argv[])
{
  int nlines, c;
  int numeric = 0;
  int reverse = 0;
  int fold = 0;
  int directory = 0;
  unsigned long line_length = LINELENGTH;

  while (--argc > 0 && ((*(++argv))[0] == '-'))
  {
    c = (++(*argv))[0];
    switch (c)
    {
    case 'n':
      numeric = 1;
      break;
    case 'r':
      reverse = 1;
      break;
    case 'f':
      fold = 1;
    case 'd':
      directory = 1;
    default:
      break;
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES, line_length)) >= 0)
  {
    my_qsort((void **)lineptr, 0, nlines - 1, numeric ? numcmp : my_strcmp, reverse, fold, directory);
    writelines(lineptr, nlines);
    return 0;
  }
  else
  {
    printf("input too big to sort\n");
    return 1;
  }
}

int my_getline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
  {
    s[i] = c;
  }

  if (c == '\n')
  {
    s[i++] = c;
  }
  s[i] = '\0';
  return i;
}

int readlines(char *line_ptr[], int maxlines, int line_length)
{
  int len, nlines;
  char *p, line[LINELENGTH];

  nlines = 0;
  while ((len = my_getline(line, line_length)) > 0)
  {
    if (nlines > maxlines || (p = malloc(len)) == NULL)
    {
      return -1;
    }
    else
    {
      (line)[len - 1] = '\0';
      strcpy(p, line);
      line_ptr[nlines++] = p;
    }
  }
  return nlines;
}

void writelines(char *lineptr[], int nlines)
{
  for (int i = 0; i < nlines; i++)
  {
    printf("%s\n", lineptr[i]);
  }
}

void my_qsort(void *v[], int left, int right,
              int (*comp)(void *, void *, int, int, int), int reversed, int fold, int directory)
{
  int i, last;
  void swap(void *[], int, int);

  if (left >= right)
  {
    return;
  }

  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
  {
    if ((*comp)(v[i], v[left], reversed, fold, directory) < 0)
    {
      swap(v, ++last, i);
    }
  }

  swap(v, left, last);
  my_qsort(v, left, last - 1, comp, reversed, fold, directory);
  my_qsort(v, last + 1, right, comp, reversed, fold, directory);
}

int numcmp(char *s1, char *s2, int reversed, int fold)
{
  double v1, v2;
  int result = 0;
  reversed = reversed ? -1 : 1;

  char copy_1[LINELENGTH];
  char copy_2[LINELENGTH];

  if (fold)
  {
    strcpy(copy_1, s1);
    strcpy(copy_2, s2);
    strlwr(copy_1);
    strlwr(copy_2);

    v1 = atof(copy_1);
    v2 = atof(copy_2);
  }
  else
  {
    v1 = atof(s1);
    v2 = atof(s2);
  }

  if (v1 < v2)
  {
    result = -1;
  }
  else if (v1 > v2)
  {
    result = 1;
  }

  return result * reversed;
}

int my_strcmp(const void *p1, const void *p2, int reversed, int fold, int directory)
{
  const char *s1 = p1;
  const char *s2 = p2;
  reversed = reversed ? -1 : 1;

  if (fold)
  {
    char copy_1[LINELENGTH];
    char copy_2[LINELENGTH];
    strcpy(copy_1, s1);
    strcpy(copy_2, s2);

    strlwr(copy_1);
    strlwr(copy_2);

    if (directory)
    {
      return (dircmp(copy_1, copy_2) * reversed);
    }
    return (strcmp(copy_1, copy_2) * reversed);
  }

  if (directory)
  {
    return (dircmp(s1, s2) * reversed);
  }

  return strcmp(s1, s2) * reversed;
}

void strlwr(char str[])
{
  while (*str != '\0')
  {
    *str = tolower(*str);
    str++;
  }
}

void swap(void *v[], int i, int j)
{
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int dircmp(const void *p1, const void *p2)
{
  const char *s1 = p1;
  const char *s2 = p2;

  char copy_1[LINELENGTH];
  char copy_2[LINELENGTH];
  strcpy(copy_1, s1);
  strcpy(copy_2, s2);

  collapse(copy_1);
  collapse(copy_2);

  return strcmp(copy_1, copy_2);
}

void collapse(char str[])
{
  int len = strlen(str);
  int i = 0;
  int j = 0;

  while (i < len - 1)
  {
    if (!isblank(str[i]) && !isalpha(str[i]) && !isdigit(str[i]))
    {
      j = i;
      while (j < len)
      {
        str[j] = str[j + 1];
        j++;
      }
    }
    i++;
  }
}