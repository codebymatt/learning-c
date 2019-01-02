#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int getop(char []);
void push(double);
double pop(void);

void peek(void);
void duplicate_stack(double []);
void swap_top(void);
void clear_stack(void);

float sign = 1.0;
// float num_string;

int main()
{
  int type;
  double op2;
  double op;
  double num_string;
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
        if (op2 != 0.0) {
          push((int)pop() % (int)op2);
        } else {
          printf("error: zero divisor\n");
        }
        break;
      case 's':
        push(sin(pop()));
        break;
      case 'c':
        push(cos(pop()));
        break;
      case 't':
        push(tan(pop()));
        break;
      case 'e':
        push(exp(pop()));
        break;
      case 'p':
        op2 = pop();
        push(pow(pop(), op2));
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

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}

void peek(void)
{
  if (sp > 0) {
    printf("Top of stack is: %f\n", val[sp]);
  } else {
    printf("error: stack empty\n");
  }
}

void duplicate_stack(double dup[])
{
  int i = 0;
  while (val[i] != '\0') {
    dup[i] = val[i];
  }
}

void swap(void)
{
  int temp = val[sp];
  val[sp] = val[sp - 1];
  val[sp - 1] = temp;
}

void clear_stack(void)
{
  while(sp > -1) {
    val[sp--] = 0;
  }
}


