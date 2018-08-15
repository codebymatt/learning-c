#include <stdio.h>
#define MAXLENGTH 4096

int get_line(char line[], int limit);

int main()
{
    int c, count;
    c = 0;
    count = 0;

    while (c != EOF) {
        char line[MAXLENGTH];
        c = get_line(line, MAXLENGTH);
    }
}

int get_line(char line[], int limit)
{
    int c, count;
    count = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        line[count] = c;
        count++;
    }

    if (count > 80 && count < limit - 1) {
        line[count + 1] = '\n';
        printf("%s\n", line);
    }

    return c;
}
