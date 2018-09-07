#include <stdio.h>

int main()
{
    int c;
    int lim = 100;
    char s[lim];

    for(int i=0; i<lim-1; i++) {
        if((c=getchar()) != '\n') {
            if(c != EOF) {
                s[i] = c;
            }
        }
    }
}
