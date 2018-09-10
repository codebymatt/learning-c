#include <stdio.h>

int any(char s1[], char s2[]);

int main() {
    char s1[] = "This is the first string";
    char s2[] = "first";

    char s3[] = "This is another string";
    char s4[] = "qzkp";

    printf("Character found at index %d\n", any(s1, s2));
    printf("Character found at index %d\n", any(s3, s4));
    return 0;
}

int any(char s1[], char s2[])
{
    int i, j;
    i = 0;
    char c;

    while((c = s1[i]) != '\0') {
       for(j = 0; s2[j] != '\0'; j++) {
            if(c == s2[j]) {
                return i;
            }
       }
       i++;
    }
    return -1;
}
