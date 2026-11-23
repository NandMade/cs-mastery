#include "arena.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Arena {
    size_t capacity;
    size_t offset;
    void *storage;
} Arena;

Arena *arena_create(size_t capacity) {
    Arena *new = malloc(sizeof(Arena));

    new->offset = 0;
    new->capacity = capacity;
    new->storage = malloc(capacity);

    return new;
}

bool arena_has_capacity(Arena *a, size_t size, size_t padding) {
    return a->offset + padding + size <= a->capacity;
}

size_t arena_get_offset(Arena *a) {
    return a->offset;
}

void *arena_alloc(Arena *a, size_t size, size_t align) {
    size_t requiredPadding = a->offset == 0 ? 0 : align - a->offset % align;
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
