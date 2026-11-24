#include <stddef.h>
#ifndef CUSTOM_MATH
#define CUSTOM_MATH

static inline size_t size_t_max(size_t a, size_t b) {
    return a > b ? a : b;
}

static inline size_t size_t_min(size_t a, size_t b) {
    return a < b ? a : b;
}
    
#endif
