// NOTE: This compiles, but doesn't run, primarily because I don't think I'm using getline
// correctly. The rest of the logic appears sound though, and since the purpose of playing with C
// is not to learn how getline works, I'm going to skip on ahead.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int getop(char []);
void push(double);
double pop(void);

float sign = 1.0;
float num_string;
int ind = 0;
char input_string[MAXOP];

int main()
{
  int type;
  double op2;
  char s[MAXOP];

  getline(input_string, MAXOP, stdin);

  while((type = getop(s)) != EOF) {
    switch(type) {
      case NUMBER:
        num_string = atof(s) * sign;
        push(num_string);
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '/':
        op2 = pop();
        if (op2 != 0.0) {
          push(pop() / op2);
        } else {
          printf("error: zero divisor\n");
        }
        break;
      case '%':
        op2 = pop();
        push((int)pop() % (int)op2);
        break;
      case '\n':
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }
  return 0;
}

int sp = 0;
double val[MAXVAL];

void push(double f)
{
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else {
    printf("error: stack full, can't push %g\n", f);
  }
}

double pop(void)
{
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

int getop(char s[])
{
  sign = 1.0;
  int i, c, next;

  while((s[0] = c = input_string[ind++]) == ' ' || c == '\t') {
    ;
  }

  s[1] = '\0';

  i = 0;
  if (!isdigit(c) && c != '.') {

    if (c == '-') {
      if (isdigit(next = input_string[ind++])) {
        c = next;
        s[i++] = c;
        sign = -1.0;
      } else {
        return c;
      }
    } else {
      return c;
    }
  }

  if (isdigit(c)) {
    while(isdigit(s[++i] = c = input_string[ind++])) {
      ;
    }
  }

  if (c == '.') {
    while (isdigit(s[++i] = c = input_string[ind++])) {
      ;
    }
  }
  
  s[i] = '\0';
  if (c != EOF) {
    ind--;
  }
  return NUMBER;
}


