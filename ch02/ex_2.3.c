/* Assume correct hexadecimal string is passed in */

#include <stdio.h>
#include <ctype.h>

#define MAXLENGTH 1000

int htoi(char s[]);
int readline(char s[], int limit);

int main()
{
    int len;
    char s[MAXLENGTH];

    while((len = readline(s, MAXLENGTH)) > 0) {
        int i = htoi(s);
        printf("Integer value is: %d\n\n", i);
        //printf("String value is: %s\n\n", s);
    }
    return 0;
}

int readline(char s[], int lim)
{
    int c, count;
    count = 0;

    while(count<lim && (c=getchar()) != EOF && c != '\n') {
        s[count++] = c;
    }
    s[count] = '\0';

    return count;
}

int htoi(char s[])
{
}
