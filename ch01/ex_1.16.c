#include <stdio.h>

// This is a rather arbitrary line length, but since I'm 
// not doing this with dynamic memory, it's happening
#define MAXLENGTH 4096

// Couldn't use 'getline' because apparently OSX has defined this already.
// Or so my compiler tells me anyways.
int get_line(char line[], int limit);
void copy(char to[], char from[]);

int main()
{
    int len;
    int max;
    char line[MAXLENGTH];
    char longest[MAXLENGTH];

    max = 0;
    while ((len = get_line(line, MAXLENGTH)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    
    if (max > 0) {
        printf("\nThe longest line had %d characters, it's displayed below:\n", max);
        printf("%s\n", longest);
    } else {
        printf("There was no longest line, unfortunately.\n");
    }

    return 0;
}

// This function is where our modification happens
int get_line(char line[], int limit)
{
    int i, c;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        if (i < limit - 1) {
            line[i] = c;
        }
    }

    if (c == '\n') {
        line[i] = c;
        i++;
    }

    line[i] = '\0';

    return i;
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        i++;
    }
}
