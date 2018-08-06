#include <stdio.h>

int main()
{
    int c;
    int inspace = 0;

    while ((c = getchar()) != EOF){
        if (c == ' ' || c == '\t') {
            if (inspace) {
                continue;
            } else {
                inspace = 1;
                putchar('\n');
            }
        } else {
            inspace = 0;
            putchar(c);
        }
    }
}
