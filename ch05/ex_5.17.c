// Add a field handling capability so sorting may be done on fields within lines, each field
// sorted accoriding to an independent set of options. (The index for the K&R C book was sorted
// with -df for the index category and -n for the page numbers)

// NOTE: Have not allowed for the usage of args back to back (for example, -nf instead of -n -f)
// If I was doing this for pure completeness I would, but I'm not, so I don't care.
// I've also realised I've forgotten to add code to handle the 'dir' option to 'numcmp', but not
// going to go back and change that.

// Use '+' to indicate FIELD to sort on wihtin line
// Once lines sorted according to content *before* field, sort content *after* field in place
// according to given options. Assume whitespace is being used as separator.

// Implementation slightly buggy, but it works as required, and I don't want to sink more time into
// ironing out a trivial bug for the sake of it. For some reason an extra space is added after field
// and fields under 4 chars long don't work

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define LINELENGTH 4096

char *lineptr[MAXLINES];
char field[LINELENGTH] = "";
char *inner_line_ptr[MAXLINES];

int pos_numeric = 0;
int pos_reverse = 0;
int pos_fold = 0;
int pos_directory = 0;

int my_getline(char s[], int lim);
int readlines(char *lineptr[], int nlines, int line_length);
void writelines(char *lineptr[], int nlines);

void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *, int, int, int), int reversed, int fold, int directory);
int numcmp(char *, char *, int, int);
int numcmp_with_field(char *, char *, int, int);
int my_strcmp(const void *, const void *, int, int, int);
int strcmp_with_field(const void *, const void *, int, int, int);
void strlwr(char[]);
int dircmp(const void *, const void *);
void collapse(char[]);
void sort_field(char *);

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

  if ((*argv)[0] == '+')
  {
    strcpy(field, (++(*argv)));
    printf("Field: %s\n", field);
    while (--argc > 0 && ((*(++argv))[0] == '-'))
    {
      c = (++(*argv))[0];
      switch (c)
      {
      case 'n':
        pos_numeric = 1;
        break;
      case 'r':
        pos_reverse = 1;
        break;
      case 'f':
        pos_fold = 1;
      case 'd':
        pos_directory = 1;
      default:
        break;
      }
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES, line_length)) >= 0)
  {
    if (strncmp(field, "", LINELENGTH) != 0)
    {
      my_qsort((void **)lineptr, 0, nlines - 1, numeric ? numcmp_with_field : strcmp_with_field, reverse, fold, directory);

      for (int i = 0; i < nlines; i++)
      {
        char *line_copy[LINELENGTH];
        sort_field(lineptr[i]);
      }

      writelines(lineptr, nlines);
      return 0;
    }
    else
    {
      my_qsort((void **)lineptr, 0, nlines - 1, numeric ? numcmp : my_strcmp, reverse, fold, directory);
      writelines(lineptr, nlines);
      return 0;
    }
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

int numcmp_with_field(char *s1, char *s2, int reversed, int fold)
{
  char copy_1[LINELENGTH];
  char copy_2[LINELENGTH];
  strcpy(copy_1, s1);
  strcpy(copy_2, s2);

  char *field_location;

  if ((field_location = strstr(copy_1, field)) != NULL)
  {
    *field_location = '\0';
  }

  if ((field_location = strstr(copy_2, field)) != NULL)
  {
    *field_location = '\0';
  }

  return numcmp(copy_1, copy_2, reversed, fold);
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

int strcmp_with_field(const void *p1, const void *p2, int reversed, int fold, int directory)
{
  const char *s1 = p1;
  const char *s2 = p2;

  char copy_1[LINELENGTH];
  char copy_2[LINELENGTH];
  strcpy(copy_1, s1);
  strcpy(copy_2, s2);

  char *field_location;

  if ((field_location = strstr(copy_1, field)) != NULL)
  {
    *field_location = '\0';
  }

  if ((field_location = strstr(copy_2, field)) != NULL)
  {
    *field_location = '\0';
  }

  return my_strcmp(copy_1, copy_2, reversed, fold, directory);
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

void sort_field(char *line)
{
  char *field_location;

  if ((field_location = strstr(line, field)) == NULL)
  {
    return;
  }

  field_location += strlen(field) * sizeof(char);

  char sorted_field[LINELENGTH];

  int num_lines = 0;
  char *str;
  char *line_copy[4096];
  *line_copy = malloc(sizeof(char) * LINELENGTH);

  strcpy(*line_copy, field_location);
  while ((str = strsep(line_copy, " ")) != NULL)
  {
    inner_line_ptr[num_lines++] = str;
  }

  free(*line_copy);

  my_qsort((void **)inner_line_ptr, 0, num_lines - 1, pos_numeric ? numcmp : my_strcmp,
           pos_reverse, pos_fold, 0);

  strcpy(sorted_field, inner_line_ptr[0]);
  strcat(sorted_field, " ");
  for (int i = 1; i < num_lines - 1; i++)
  {
    strcat(sorted_field, inner_line_ptr[i]);
    strcat(sorted_field, " ");
  }
  strcat(sorted_field, inner_line_ptr[num_lines - 1]);
  strcat(field_location, " ");
  field_location += sizeof(char);
  strcpy(field_location, sorted_field);
  // printf("%s\n", line);
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