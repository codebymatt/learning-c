#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
    printf("Range of several variable types in C (using header constants):\n\n");

    printf("range of signed char:       %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("range of unsigned char:     %d to %d\n\n", CHAR_MIN, UCHAR_MAX);
    
    printf("range of signed short:      %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("range of unsigned short:    %d to %d\n\n", 0, USHRT_MAX);

    printf("range of signed long:       %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("range of unsigned long:     %d to %lu\n\n", 0, ULONG_MAX);
    
    printf("range of signed double:     %lf to %lf\n\n", DBL_MIN, DBL_MAX);

    printf("Range of several variable types in C (computed):\n\n");
}
