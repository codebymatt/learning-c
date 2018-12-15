#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// I use `atofl` instead of `atof` because I want to use atoi to convert the
// any exponent given to an int. The stdlib already declares `atof`, so I
// needed a new function name.
double atofl(char s[]);

int main()
{
    char s[4096];

    scanf("%s", s);
    double f = atofl(s);

    printf("Floating value is %f\n", f);
}

double atofl(char s[])
{
    double val, power;
    power = 0;

    int i, sign;

    for (i = 0; isspace(s[i]); i++)
        ;
    
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }

    if (s[i] == '.') {
        i++;
    }

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E') {
        int exp, exp_sign;
        i++;

        exp_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-') {
            i++;
        }

        // Probably didn't need this, only handles e-6 (that's the precision of a float),
        // so could error for smaller/larger exponent values
        exp = atoi(&s[i]);

        if (exp_sign < 0 && exp > 0) {
            for(i = 0; i < exp; i++) {
                power *= 10;
            }
        } else if (exp_sign > 0 && exp > 0) {
            for(i = 0; i < exp; i++) {
                power /= 10;
            }
        }
    }

    return sign * val / power;
}