#include <stdio.h>

int my_strend(char *s, char *t);

int main()
{
  int MAX_SIZE = 100;
  char first[MAX_SIZE];
  char second[MAX_SIZE];

  scanf("%s", first);
  scanf("%s", second);

  int result = my_strend(first, second);
  printf("%d\n", result);
}

int my_strend(char *s, char *t)
{
  // Alternate approach could be to count lengths, then compare backwards
  // (while backward counter < length of t)

  int s_len, t_len;
  s_len = t_len = 0;

  while(*s++ != '\0') {
    s_len++;
  }

  while(*t++ != '\0') {
    t_len++;
  }

  if (s_len < t_len) {
    return 0;
  }

  s -= (s_len + 1); t -= (t_len + 1);

  s += (s_len - t_len);

  while(*s != '\0') {
    if (*s == *t) {
      s++; t++;
    } else {
      return 0;
    }
  }

  return 1;
}