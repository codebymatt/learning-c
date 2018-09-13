#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
    unsigned x;
    int p, n;
    p = n = 2; // HARDCODED

    scanf("%u", &x);
    x = invert(x, p, n);
    printf("%d\n", x);
}

unsigned invert(unsigned x, int p, int n)
{
    unsigned temp = x;

    temp >>= p;
    temp = ~temp;
    temp &= ~(~0 << n);
    temp <<= p;
    x |= temp;
    
    temp >>= p;
    temp |= (~0 << n); 
    temp <<= p;
    temp |= ~(~0 << p);
    x &= temp;

    return x;
}
