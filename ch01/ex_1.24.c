// Check for unbalanced parentheses, brackets, and braces only
#include <stdio.h>
#define MAXLENGTH 4096

/* WILL RETURN TO THIS EXERCISE */

int main()
{
  int c;
  int brackets, parens, braces;
  brackets = parens = braces = 0;

  while ((c = getchar()) != EOF)
  {
    switch (c)
    {
    case '(':
      parens++;
      break;
    case '{':
      braces++;
      break;
    case '[':
      brackets++;
      break;
    case ')':
      parens--;
      break;
    case '}':
      braces--;
      break;
    case ']':
      brackets--;
      break;
    }
  }

  if (brackets != 0 || braces != 0 || parens != 0)
  {
    printf("Unbalanced syntax!\n");
    printf("\tBrackets: %i\n", brackets);
    printf("\tBraces: %i\n", braces);
    printf("\tParentheses: %i\n", parens);
  }
  else
  {
    printf("Everything looks balanced!\n");
  }

  return 0;
}
