#include <stdio.h>
#define swap(t, x, y) t temp = x; x = y; y = temp;

int main()
{
  int a = 1;
  int b = 2;

  swap(int, a, b);

  printf("a is %d, b is %d\n", a, b);
  
  return 0;
}