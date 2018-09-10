#include <stdio.h>

void squeeze(char s1[], char s2[]);
int char_in_string(char c, char s[]);

int main()
{
    char s1[] = "The quick brown fox jumped over the lazy dog";
    char s2[] = "quickbrown";
    squeeze(s1, s2);
    printf("%s\n", s1); 
}

void squeeze(char s1[], char s2[])
{
    int i,j;
    for(i = j = 0; s1[i] != '\0'; i++) {
        if(!char_in_string(s1[i], s2)) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}

int char_in_string(char c, char s[])
{
    int i, in_string;
    in_string = 0;
    for(i = 0; s[i] != '\0'; i++) {
        if(s[i] == c) {
            in_string = 1;
        }
    }
    return in_string;
}
