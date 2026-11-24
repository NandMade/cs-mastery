#include "int_math.h"
#include <stdint.h>

// x^9  = x^8 * x
//      = x^2 * x^2 * x^2 * x
//      = x^2^3 * x
bool size_pow(size_t base, size_t exponent, size_t *out) {
    size_t result = 1;

    while (exponent > 0) 
    {
        if (exponent & 1) 
        {
            if (base > 0 && SIZE_MAX / base < result) 
            {
                *out = SIZE_MAX;

                return false;
            }
            result *= base;
        }
        
        exponent >>= 1;

        if (base > 0 && SIZE_MAX / base < base)
        {
            *out = SIZE_MAX;

            return false;
        }
        base *= base;
    }

    *out = result;

    return true;
}



