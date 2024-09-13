#include "cvector.h"
#include <stdio.h>


int main()
{
    cvector_t x = cvector(int, 324);
    printf("%zu\n", x.capacity(&x));
    return 0;
}
