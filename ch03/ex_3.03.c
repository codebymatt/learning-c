#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLENGTH 4096

void escape(char s1[], char s2[]);

int main()
{
    char input[MAXLENGTH];
    char output[MAXLENGTH];

    fgets(input, MAXLENGTH, stdin);
    escape(input, output);

    printf("%s\n", output);

    return 0;
}

void escape(char s1[], char s2[])
{
    int i = 0;
    int j = 0;
    int len = strlen(s1);

    if (len < 3) {
        for (int k=0; k<len; k++) {
            s2[j++] = s1[i++];
        }
    }

    while( i < len - 2) {
        if( isalnum(s1[i]) && (s1[i+1] == '-') && isalnum(s1[i+2])) {
            int low = s1[i];
            int high = s1[i+2];
            if (low < high) {
                for(int k = low; k <= high; k++) {
                    s2[j++] = k;
                }
                i += 3;
            } else {
                for(int k = 3; k > 0; k--) {
                    s2[j++] = s1[i++];
                }
            }
        } else {
            s2[j++] = s1[i++];
        }
    }

    while(s1[i] != '\0') {
        s2[j++] = s1[i++];
    }

    s2[j] = '\0';
}