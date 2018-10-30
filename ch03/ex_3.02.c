#include <stdio.h>
#define MAXLENGTH 1000

void escape(char s[], char t[]);

int main()
{
    char line[MAXLENGTH];
    char newline[MAXLENGTH * 2];

    int c;
    int count = 0;

    while ((c = getchar()) != EOF && count < MAXLENGTH) {
        line[count++] = c;
    }
    line[count] = '\0';

    escape(line, newline);
    printf("%s\n", newline);

    return 0;
}

void escape(char s[], char t[])
{
    int i, j;
    i = j = 0;
    while(s[i] != '\0') {
        switch (s[i]) {
            case '\n':
                t[j++] = '\\';
                t[j] = 'n';
                break;
            case '\t':
                t[j++] = '\\';
                t[j] = 't';
                break;
            default:
                t[j] = s[i];
                break;
        }
        i++, j++;
    }
    t[j] = '\0';
}