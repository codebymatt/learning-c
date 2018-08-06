#include <stdio.h>

int main()
{
	printf("Press a key (any key!) and then press enter\n");
	printf("The expression 'getchar != EOF' evaluates to %d\n", getchar() != EOF);

	return 0;
}
