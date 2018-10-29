#include <stdio.h>

// x - 1 will always have a different value in the rightmost bit compared to x, but all the other
// bits will be the same (except the second to last rightmost bit at times).
// Using the '&' operator means these differing bits will resolve to 0 in x,
// While all other bits in x will remain the same.

int bitcount(unsigned x);

int main()
{
    unsigned x;
    
    scanf("%u", &x);
    printf("%u\n", bitcount(x));

    return 0;
}

int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x &= (x - 1)) {
        if (x | 0) {
            b++;
        }
    }
    return b;
}