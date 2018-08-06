#include <stdio.h>

int main()
{
    // I could draw the bars vertically, but there are 
    // more interesting problems in the world to tackle
    
    int c;
    int count_frequency[10] = {0};
    int in_word = 0;
    int count = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (in_word) {
                if (count < 10) {
                    count_frequency[count - 1]++;
                } else {
                    count_frequency[9]++;
                }
                in_word = 0;
            }
            count = 0;
        } else {
            in_word = 1;
            count++;
        }
    }

    for (int i = 0; i < 9; i++) {
        printf(" %d ", i + 1);
        for (int j = 0; j < count_frequency[i]; j++) {
            putchar('#');
        }
        printf("\n");
    }

    printf(">9 ");
    if (count_frequency[9] > 80) {
        printf("TOO MANY TO SHOW");
    } else {
        for (int j = 0; j < count_frequency[9]; j++) {
            putchar('#');
        }
    }

    printf("\n");
}
