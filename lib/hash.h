#ifndef HASH_FUNCTIONS
#define HASH_FUNCTIONS
#include <stdint.h>
#include "types.h"
#include <stddef.h>

uint64_t hash_fnv1a(byte *start, size_t length);

#endif