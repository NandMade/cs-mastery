#include <stdio.h>

#ifndef CHECK_MODULE
#define CHECK_MODULE

static int failures = 0;

#define CHECK(cond) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", \
                    __FILE__, __LINE__, #cond); \
            failures++; \
        } \
    } while (0) \

#endif
