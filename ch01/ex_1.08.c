#include <stdio.h>

int main()
{
	int c, tabCount, blankCount, newlineCount;
	blankCount = tabCount = newlineCount = 0;

	while ((c = getchar()) != EOF){
		if (c == ' ') {
			blankCount++;
		} else if (c == '\t') {
			tabCount++;
		} else if (c == '\n') {
			newlineCount++;
		}
	}
	
	// I haven't accounted for plurals,
	// because that would be tedious.

	printf("There were %d blanks\n", blankCount);
	printf("There were %d tabs\n", tabCount);
	printf("There were %d newlines\n", newlineCount);
}
