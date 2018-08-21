#include <stdio.h>
#define MAXLENGTH 4096
#define TABLENGTH 4

int get_line(char line[], int limit);
int get_line_length(char line[]);
void copy_untabbed_to_tabbed(char untabbed[], char tabbed[]);

int main()
{
    int length;
    char untabbed[MAXLENGTH];
    char tabbed[MAXLENGTH];
    while ((length = get_line(untabbed, MAXLENGTH)) > 0) {
        copy_untabbed_to_tabbed(untabbed, tabbed);
        printf("%s", tabbed);
    }

    return 0;
}

int get_line(char line[], int limit)
{
    int c, count;
    count = 0;
    while((c = getchar()) != EOF && c != '\n' && count < limit - 1) {
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

int get_line_length(char line[])
{
    int count = 0;
    while (line[count] != '\0') {
        count ++;
    }

    return count;
}

void copy_untabbed_to_tabbed(char untabbed[], char tabbed[])
{
    int num_tabs, num_spaces;
    int u = 0;
    int t = 0;
    int space_count = 0;

    int l = get_line_length(untabbed);
    while (u < l) {
        if (untabbed[u] != ' ') {
            tabbed[t] = untabbed[u];
            u++;
            t++;
        } else {
            while (untabbed[u] == ' ') {
                space_count++;
                u++;
            }
            
            num_spaces = space_count % TABLENGTH;
            num_tabs = (space_count - num_spaces) / TABLENGTH;
            for (int i=0; i<num_tabs; i++) {
                tabbed[t] = '\t';
                t++;
            }
            for (int i=0; i<num_spaces; i++) {
                tabbed[t] = ' ';
                t++;
            }

            space_count = 0;
        }
    }

    tabbed[t] = '\0';
}
