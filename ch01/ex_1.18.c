#include <stdio.h>
#define MAXLENGTH 4096

int get_line(char line[], int line_limit);
int get_line_length(char line[]);
int strip_whitespace_from_line_and_return_new_length(char line[], int length);
void print_line_with_new_length(char line[], int length);

int main()
{
    int c = 0;
    int length = 0;

    while (c != EOF) {
        char line[MAXLENGTH];
        c = get_line(line, MAXLENGTH);
        length = get_line_length(line);
        length = strip_whitespace_from_line_and_return_new_length(line, length);
        if (length > 0 && line[0] != '\n') {
            print_line_with_new_length(line, length);
        }
    }
}

int get_line(char line[], int limit)
{
    int c;
    int count = 0;
    while (((c = getchar()) != EOF) && count < limit-1 && c != '\n') {
        line[count] = c;
        count++;
    }

    if (c == '\n') {
        line[count] = c;
    }

    line[count+1] = '\0';
    return c;
}

int get_line_length(char line[])
{
    int i = 0;
    while (line[i] != '\0') {
        i++;
    }

    return i;
}

int strip_whitespace_from_line_and_return_new_length(char line[], int length)
{
    int i = length - 2; // Account for new line appended at end
    while (line[i] == ' ' || line[i] == '\t') {
        i--;
    }

    return i+1;
}

void print_line_with_new_length(char line[], int length)
{
    for (int i = 0; i < length; i++) {
        putchar(line[i]);
    }
    putchar('\n');
}
