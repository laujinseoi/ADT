#include <stdlib.h>

int64_t fib(int n)
{
    int64_t f = 0, g = 1;
    while (0 < n--) 
    {
        g += f;
        f = g - f;
    }
    return f;
}