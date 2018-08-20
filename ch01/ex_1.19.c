#include <stdio.h>
#define MAXLENGTH 4096

int get_line(char line[], int limit);
int get_line_length(char line[]);
void reverse(char string[], int length);

int main()
{
    int c, l;
    c = 0;

    while(c != EOF) {
        char line[MAXLENGTH];
        c = get_line(line, MAXLENGTH);
        l = get_line_length(line);
        reverse(line, l);
        printf("%s\n", line);
    }

    return 0;
}

int get_line(char line[], int limit)
{
    int c, count;
    count = 0;

    while ((c = getchar()) != EOF && c != '\n' && count < limit-1) {
        line[count] = c;
        count++;
    }

    if (c == '\n') {
        line[count] = c;
        count++;
    }

    line[count] = '\0';
    return c;
}

int get_line_length(char line[])
{
    int count = 0;
    while(line[count] != '\0') {
        count++;
    }

    return count;
}

void reverse(char line[], int length)
{
    // Account for newline character at end of string
    // and zero-indexing (in for loop)
    length = length - 2;
    int halfway = (length + 1) / 2;
    int lower, higher;

    for (int i=0; i<halfway; i++) {
        lower = line[i];
        higher = line[length-i];
        line[i] = higher;
        line[length-i] = lower;
    }
}
