#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLENGTH 4096

void escape(char s1[], char s2[]);

int main()
{
    char input[MAXLENGTH];
    char output[MAXLENGTH];

    scanf("%s", input);
    escape(input, output);

    printf("%s\n", output);

    return 0;
}

void escape(char s1[], char s2[])
{
    int i = 0;
    int k = 0;
    int len = strlen(s1);

    if ( len < 3) {
        return;
    }

    while(i < len - 2) {
        if((s1[i+1] == '-') && (isalnum(s1[i])) && (isalnum(s1[i+2]))) {
            // s2[k++] = s1[i];
            if (s1[i] < s1[i+2]) {
                for (int j = s1[i]; j <= s1[i+2]; j++) {
                    s2[k++] = j;
                }
                i += 3;
            } else {
                s2[k++] = s1[i++];
            }
        } else {
            s2[k++] = s1[i++];
        }
    }

    while(i < len) {
        s2[k++] = s1[i++];
    }
    s2[k] = '\0'; 
}