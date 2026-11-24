#include <stdio.h>

#ifndef CHECK_MODULE
#define CHECK_MODULE

static int failures = 0;

#define CHECK(cond, msg) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n, msg: %s", \
                    __FILE__, __LINE__, #cond, msg); \
            failures++; \
        } \
    } while (0) \

#endif
