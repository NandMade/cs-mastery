#ifndef HASH_FUNCTIONS
#define HASH_FUNCTIONS
#include "types.h"
#include <stddef.h>
#include <stdint.h>

uint64_t hash_fnv1a(byte *start, size_t length);
uint64_t string_hash_fnv1a(char *start);

#endif