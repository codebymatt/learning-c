// Simplified version from Ch4, with only 4 basic arithmetic operators,
// positive single digit operands, no floats, and no error handling.

#include <stdio.h>
#include <ctype.h>
#define MAX_BUF 100

char pop(void);
char peek(void);
void push(char);

int stack[MAX_BUF];
int tracker = 0;
int main(int argc, char *argv[])
{
  int c, temp, op2;

  while (--argc > 0)
  {
    c = **(++argv);

    if (isdigit(c))
    {
      push(c - '0');
    }
    else
    {
      switch (c)
      {
      case '+':
        push(pop() + pop());
        break;
      case '-':
        temp = pop();
        push(pop() - temp);
        break;
      case 'x':
        push(pop() * pop());
        break;
      case '/':
        temp = pop();
        if (temp == 0)
        {
          printf("Can't divide by 0!");
          return 1;
        }
        push(pop() / temp);
        break;
      default:
        printf("Invalid input!\n");
        break;
      }
    }
  }
  printf("%d\n", pop());
  return 0;
}

char pop(void)
{
  if (tracker > 0)
  {
    char temp = stack[tracker - 1];
    tracker--;
    return temp;
  }
  else
  {
    printf("Stack is empty!\n");
    return 0;
  }
}

char peek(void)
{
  if (tracker > 0)
  {
    return stack[tracker - 1];
  }
  else
  {
    printf("Stack is empty!\n");
    return 0;
  }
}

void push(char c)
{
  stack[tracker++] = c;
}
