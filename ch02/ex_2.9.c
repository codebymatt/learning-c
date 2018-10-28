#include <stdio.h>

// Use this observation to write a faster version of bitcount .

// x - 1 will always have a different value in the rightmost bit compared to x, but all the other
// bits will be the same (except the second to last rightmost bit at times).
// Using the '&' operator means these differing bits will resolve to 0 in x,
// While all other bits in x will remain the same.

int main()
{
    return 0;
}