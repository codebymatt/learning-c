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

    printf("range of signed int:        %d to %d\n", INT_MIN, INT_MAX);
    printf("range of unsigned int:      %d to %u\n\n", 0, UINT_MAX);

    printf("range of signed long:       %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("range of unsigned long:     %d to %lu\n\n", 0, ULONG_MAX);
    
    printf("range of signed float:      %e to %e\n\n", FLT_MIN, FLT_MAX);
    printf("range of signed double:     %e to %e\n\n", DBL_MIN, DBL_MAX);

}
