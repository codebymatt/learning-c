#include <stdio.h>

int main()
{
	/* Using an invalid escape sequence generates a compiler warning (like so) */
	printf("\c");
}
