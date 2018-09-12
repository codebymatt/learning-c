#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
    unsigned x, y; 
    int p, n;
    p = n = 2;
    y = 1;

    scanf("%u", &x);
    x = setbits(x, p, n, y);
    printf("%u\n", x);
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    // I was gonna leave comments here for future Matt, but...
    // THIS EXERCISE IS LEFT TO THE READER
    y = y & ~(~0 << n); 
    y = y << p; 
    x = x | y;

    y = y >> p;

    y = y | (~0 << n);
    y = y << p;
    y = y | ~(~0 << n);
    x = x & y;

    return x;
}
