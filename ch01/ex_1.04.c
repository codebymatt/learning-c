#include <stdio.h>

int main()
{
	float celsius, fahr;
	int lower, upper, step;
	
	lower = 0;
	upper = 200;
	step = 10;

	celsius = lower;
	printf("Celsius\t Fahrenheit\n");
	while (celsius <= upper) {
		fahr = (celsius * (9.0/5.0)) + 32.0;
		/* No need for decimals in the output (the math works out such that all results will be integers) */
		printf("%7.f\t %10.f\n", celsius, fahr);
		celsius = celsius + step;
	}	
}
