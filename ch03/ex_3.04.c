// In a two's complement system, the negatve value of a positive binary number is found by inverting
// all bits and adding one. Passing in the largest negative number (NEG) will result in NEG being
// multiplied by -1 in the K&R implementation of `itoa`. However that will invert all bits,
// (resulting in a leading 0 and n-1 trailing 1-bits, where n == word-size), and then add one,
// which in turn will result in a leading 1-bit followed by n-1 trailing 0-bits. This, however, is
// the original number NEG we started with. In `itoa` a test is made: while (n /= 10) > 0. If using
// n == NEG here, that value will straightaway be false, and thus the loop will cut off after one
// iteration.

// In hindsight that explanation may not be entirely lucid, but it's late and I just spent a bunch
// of time correcting my previously wrong understanding of how two's complement works.

void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }

    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10)); // The condition here used to be '(n /= 10) > 0'

    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}
