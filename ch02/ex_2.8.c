#include <stdio.h>

unsigned long rightrot(unsigned long x, int n);

int main()
{
    unsigned long x;
    int n = 2; // Hardcoded

    scanf("%lu", &x);
    x = rightrot(x, n);
    printf("Your number inverted is: %lu\n", x);

    return 0;
}

unsigned long rightrot(unsigned long x, int n)
{
    unsigned long temp = x;

    temp &= ~(~0 << n);
    x >>= n;
    temp <<= (sizeof(x) - n);
    x |= temp;
    
    return x;
}