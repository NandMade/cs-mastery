#ifndef HASH_FUNCTIONS
#define HASH_FUNCTIONS
#include "types.h"
#include <stddef.h>
#include <stdint.h>

uint64_t hash_fnva1(byte *start, size_t length);
uint64_t string_hash_fnva1(const char *start);

#endif