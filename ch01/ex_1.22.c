// We choose n = 10 for this exercise (for easy testing purposes)

#include <stdio.h>
#define LIMIT 10
#define MAXLENGTH 4096

int read_line(char line[], int limit);
void copy(int from_location, char from[], char to[]);
void split(char original[], int length);

int main()
{
    int length;
    char line[MAXLENGTH];
    while((length = read_line(line, MAXLENGTH)) > 0) {
        if (length >= LIMIT) {
            split(line, length);
        } else {
            printf("%s", line);
        }
    }
}

int read_line(char line[], int lim)
{
    int c, count;
    c = count = 0;
    while((c = getchar()) != EOF && c != '\n' && count < lim-1) {
        line[count++] = c;  
    }

    if (c == '\n') {
        line[count++] = '\n';
    }

    line[count] = '\0';
    return count;
}

void split(char original[], int length)
{
    char next[MAXLENGTH];
    int cutoff;
    if (length <= LIMIT) {
        printf("%s", original);
        return;
    } else {
        cutoff = LIMIT - 1;
    }
    
    while (cutoff > 0 && (original[cutoff] == '\t' || original[cutoff] == ' ')) {
        cutoff--;
    }

    if (cutoff == 0) {
        copy(LIMIT, original, next);
        original[LIMIT] = '\0';
        printf("%s\n", original);
        split(next, length - LIMIT);
    } else {
        copy(cutoff+1, original, next);
        original[cutoff+1] = '\0';
        printf("%s\n", original);
        split(next, length - cutoff);
    }
}

void copy(int from_location, char from[], char to[] )
{
    int f, t;
    t = 0;
    f = from_location;

    while (from[f] != '\0') {
        to[t++] = from[f++];
    }
    to[t] = '\0';
}
