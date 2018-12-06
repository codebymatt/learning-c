// NOTE: Only continuous strings are used (so two words with a
// space will be treated like a base and search string)

#include <stdio.h>

int strrindex(char base[], char search[]);

int main()
{
    char base[4096]; char search[4096];

    scanf("%s", base);
    scanf("%s", search);

    int position = strrindex(base, search);

    printf("Substring last occurs at index: %d\n", position);
}

int strrindex(char base[], char search[])
{
    int match_index = -1;
    int i, j, k;

    for (i = 0; base[i] != '\0'; i++) {
        for (j=i, k=0; search[k] != '\0' && base[j]==search[k]; j++, k++) {
            ;
        }
        if (k > 0 && search[k] == '\0') {
            match_index = i;
        }
    }
    
    return match_index;
}