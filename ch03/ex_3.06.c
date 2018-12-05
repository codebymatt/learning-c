#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int min_width);

void reverse(char s[]);

int main()
{
    int input;
    scanf("%d", &input);

    char str[64];

    itoa(input, str, 6);

    printf("%s\n", str);
}

void itoa(int n, char s[], int min_width)
{
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }

    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    while (i < min_width) {
        s[i++] = ' ';
    }

    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}