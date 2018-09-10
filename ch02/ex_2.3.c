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
        printf("Decimal value is: %d\n\n", i);
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
    int i, n, len, multiplier;
    char c;
    i = n = len = 0;
    multiplier = 1;

    while(s[len] != '\0') {
        len++;
    }

    if(s[i] == '0' && (s[i+1] == 'x' || s[i+1] == 'X')) {
        i+=2;
    }

    while(len - 1 >= i) {
        c = s[len-1];
        if (c >= '0' && c <= '9') {
            c = c - '0';
        } else {
            c = toupper(c) - 'A' + 10;
        }
        n = n + (multiplier * c);

        len--;
        multiplier *= 16;
    }
    return n;
}
