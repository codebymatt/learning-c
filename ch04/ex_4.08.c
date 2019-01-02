#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
// #define BUFSIZE 1

int getop(char []);
void push(double);
double pop(void);

float sign = 1.0;
float num_string;

int main()
{
  int type;
  double op2;
  char s[MAXOP];

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

int getch(void);
void ungetch(int);

int getop(char s[])
{
  sign = 1.0;
  int i, c, next;

  while((s[0] = c = getch()) == ' ' || c == '\t') {
    ;
  }

  s[1] = '\0';

  i = 0;
  if (!isdigit(c) && c != '.') {

    if (c == '-') {
      if (isdigit(next = getch())) {
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
    while(isdigit(s[++i] = c = getch())) {
      ;
    }
  }

  if (c == '.') {
    while (isdigit(s[++i] = c = getch())) {
      ;
    }
  }
  
  s[i] = '\0';
  if (c != EOF) {
    ungetch(c);
  }
  return NUMBER;
}

char buffer;
int buffer_empty = 0;

int getch(void)
{
  if (buffer_empty == 1) {
    return getchar();
  } else {
    buffer_empty = 1;
    return buffer;
  }
}

void ungetch(int c)
{
  buffer_empty = 0;
  buffer = c;
}


