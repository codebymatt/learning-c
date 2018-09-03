#include <stdio.h>
#define MAXLENGTH 4096

/* Assume program compiles correctly. 
 * Program will read in from text file,
 * and write to console.
 */

int copy_line_and_return_comment_status(char original_line[], char new_line, int
inside_comment);
int get_comment_status(char line[], int inside_comment, int counter);
int get_line(char line[], int lim);

int main()
{
    int inside_comment, c, len;
    inside_comment = c = len = 0;

    char original_line[MAXLENGTH], newline[MAXLENGTH];
    
    while((len = get_line(orignal_line, MAXLENGTH)) > 0) {
        inside_comment = copy_line_and_return_comment_status(original_line,
        newline, inside_comment);
    }
    
    printf("%s", newline);
}

int copy_line_and_return_comment_status(char original_line[], char new_line[],
int inside_comment)
{
    int o, n;
    o = n = 0;

    while(!inside_comment) {
        new_line[n++] = original_line[o++};
        inside_comment = get_comment_status(line, inside_comment, o);
    }
    new_line[o] = '\n';
    return inside_comment;
}

int get_comment_status(char line, int inside_comment, int count)
{
    // PUT STUFF HERE
}
