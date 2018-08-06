#include <stdio.h>

int main()
{
    int c;
    int input_arr[63] = {0};

    while ((c = getchar()) != EOF) {
        if (c <= 127 && c >= 65) {
            input_arr[c - 65]++;
        } else {
            input_arr[62]++;
        }
    }

    for (int i = 0; i < 63; i++) {
        if (i == 62) {
            printf(" other characters ");
        } else {
            printf("                %c ", i + 65);
        }

        for (int j = 0; j < input_arr[i]; j++) {
            putchar('#');
        }
        putchar('\n');
    }
}
