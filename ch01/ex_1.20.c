#include <stdio.h>
#define MAXLENGTH 4096

// Tabs in my editor are currently taking up 4 spaces, so that shall be their
// replacement value in this program. Tab stop number has been arbitrarily
// chosen to be 5
#define TABNUM 5
#define TABLENGTH 4

// I've also chosen not to modify the array in place, but to create a new array
// and copy the characters over (with tabs replaced as required)

void replace_tabs_with_spaces(char old[], char new[]);
int get_line(char line[], int limit);

int main()
{
    int length;
    char tabbed_line[MAXLENGTH];
    char spaced_line[MAXLENGTH];

    while ((length = get_line(tabbed_line, MAXLENGTH)) > 0) {
        replace_tabs_with_spaces(tabbed_line, spaced_line);
        printf("%s", spaced_line);    
    }

    return 0;
}

int get_line(char line[], int limit)
{
    int c, count;
    count = 0;

    while ((c = getchar()) != EOF && c != '\n' && count < limit - 2) {
        line[count] = c;
        count++;
    }

    if (c == '\n') {
        line[count] = c;
        count++;
    }
    
    line[count] = '\0';

    return count;
}

void replace_tabs_with_spaces(char tabbed[], char spaced[])
{
    int t = 0;
    int s = 0;
    while (tabbed[t] != '\0') {
        if (tabbed[t] != '\t') {
            spaced[s] = tabbed[t];
            s++; t++;
        } else {
            for (int i=0; i<TABLENGTH; i++) {
                spaced[s + i] = ' ';
            }

            s = s + 4;
            t++;
        }
    }

    spaced[s] = '\0';
}
