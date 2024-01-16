#include <stdio.h>
#include "math.h"

int main()
{
    check_version();
    
    printf("4 + 8 = %d\n", sum(4, 8));
    printf("10 + 1 = %d\n", add(10));
    printf("10 - 1 = %d\n", del(10));

    return 0;
}