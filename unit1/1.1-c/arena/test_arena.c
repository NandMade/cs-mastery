#include "arena.h"
#include "../../../lib/check.h"
#include <stdint.h>

static void test_arena_alloc_returns_correctly_aligned_pointers(void) {
    Arena *ar = arena_create(1000);

    void *thing = arena_alloc(ar, 16, 8);

    CHECK(((uintptr_t)thing & 7) == 0);
    
    void *thing2 = arena_alloc(ar, 16, 32);

    CHECK(((uintptr_t)thing2 & 31) == 0);

    CHECK((uintptr_t)thing2 - (uintptr_t)thing == 32);

    void *bigthing = arena_alloc(ar, 1000, 1000);

    CHECK(bigthing == NULL);

    arena_destroy(ar);
}

int main(void) {
    test_arena_alloc_returns_correctly_aligned_pointers();

    if (failures > 0) {
        return 1;
    }

    return 0;
}

