#include "hash.h"

static const uint64_t fnv_offset_basis_64 = 0xcbf29ce484222325;
static const uint64_t fnv_prime_64 = 0x100000001b3;

uint64_t hash_fnva1(byte *start, size_t length) {
    uint64_t hash = fnv_offset_basis_64;

    for (size_t i = 0; i < length; i++) 
    {
        hash ^= *(start + i);
        hash *= fnv_prime_64;
    }

    return hash;
}

uint64_t string_hash_fnva1(const char *start) {
    uint64_t hash = fnv_offset_basis_64;

    for (size_t i = 0; start[i] != '\0'; i++)
    {
        hash ^= *(start + i);
        hash *= fnv_prime_64;
    }

    return hash;
}