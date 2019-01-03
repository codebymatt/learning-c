#include <stdio.h>
#include <string.h>

void reverse(char [], int, int);

int main()
{
  char s[100] = "All about C";
  int len = strlen(s);

  // Decrement len so the null terminator doesn't get swapped.
  reverse(s, len-1, 0);
  printf("%s\n", s);
}

void reverse(char s[], int len, int index)
{
  if (index > len/2) {
    return;
  }

  reverse(s, len, index + 1);

  int temp = s[index];
  s[index] = s[len - index];
  s[len - index] = temp;
}