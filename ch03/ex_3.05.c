#include <stdio.h>
#include <string.h>

// Note that base 2 has been hardcoded in, if you wanted to be really
// complete you would read the base from the command line.

// I also haven't adjusted for hex values (a-f) when base 16 is used,
// primarily because it's almost bedtime.

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
    char s[64];
    int n;

    scanf("%d", &n);
    itob(n, s, 16);

    printf("%s\n", s);
    return 0;
}

void itob(int n, char s[], int b)
{
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }

    i = 0;
    do {
        s[i++] = n % b + '0';
    } while (n /= b);

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int len = strlen(s);
    int end = len - 1;
    char temp;

    for (int j = 0; j < len/2; j++, end--) {
        temp = s[j];
        s[j] = s[end];
        s[end] = temp;
    }
}