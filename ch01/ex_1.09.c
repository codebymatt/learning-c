#include <stdio.h>

int main()
{
    int c, extra_blanks;
    extra_blanks = 0;

    printf("Please enter the text you want stripped (hit enter when finished)\n");

    while ((c = getchar()) != EOF) {
        if (c == ' '){
            if (extra_blanks == 0) {
                extra_blanks = 1;
                putchar(c);
            } else {
                continue;
            }
        } else {
            extra_blanks = 0;
            putchar(c);
        }
    }
}
