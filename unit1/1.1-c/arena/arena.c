#include "arena.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "../../../lib/custom_math.h"

typedef struct Arena {
    size_t capacity;
    size_t offset;
    void *storage;
} Arena;

Arena *arena_create(size_t capacity) {
    if (capacity > PTRDIFF_MAX) return NULL;

    Arena *new = malloc(sizeof(Arena));

    new->offset = 0;
    new->capacity = capacity;
    new->storage = malloc(capacity);

    return new;
}

bool arena_has_capacity(Arena *a, size_t size, size_t padding) {
    size_t availableSpace = a->capacity - a->offset;

    if (size > availableSpace) return false;
    if (padding > availableSpace) return false;
    if (availableSpace - size < padding) return false;
    if (availableSpace - padding < size) return false;

    return true;
}

void *arena_alloc(Arena *a, size_t size, size_t align) {
    size_t requiredPadding = align - ((uintptr_t)a->storage + a->offset) % align;
    
    uintptr_t next;

    if (arena_has_capacity(a, size, requiredPadding)) 
    {
        a->offset += requiredPadding;
        next = (uintptr_t)a->storage + a->offset;
        a->offset += size;

        return (void *)next;
    }

    return NULL;
}


void arena_reset(Arena *a) {
    a->offset = 0;
}

void arena_destroy(Arena *a) {
    free(a->storage);
    free(a);
}
