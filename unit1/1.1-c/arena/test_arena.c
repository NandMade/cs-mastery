#include "arena.h"
#include "../../../lib/check.h"
#include <stdint.h>
#include <stddef.h>

static void test_arena_alloc_returns_correctly_aligned_pointers(void) {
    Arena *ar = arena_create(1000);

    void *thing = arena_alloc(ar, 16, 8);

    CHECK(thing != NULL);
    CHECK(((uintptr_t)thing & 7) == 0);
    
    void *thing2 = arena_alloc(ar, 16, 32);

    CHECK(thing2 != NULL);
    CHECK(((uintptr_t)thing2 & 31) == 0);

    void *thing3 = arena_alloc(ar, 64, 64);

    CHECK(thing3 != NULL);
    CHECK(((uintptr_t)thing3 & 63) == 0);

    arena_destroy(ar);
}

static void test_arena_alloc_absurd_inputs_return_null(void) {
    Arena *ar = arena_create(SIZE_MAX);

    CHECK(ar == NULL);

    ar = arena_create(8000);

    void *largeThing = arena_alloc(ar, SIZE_MAX, 16);

    CHECK(largeThing == NULL);

    void *largeAlignment = arena_alloc(ar, 16, SIZE_MAX);

    CHECK(largeAlignment == NULL);

    arena_destroy(ar);
}

static void test_arena_alloc_exhausted_returns_null(void) {
    Arena *ar = arena_create(8000);

    arena_alloc(ar, 4000, 8);
    void *thing2 = arena_alloc(ar, 4001, 8);

    CHECK(thing2 == NULL);

    arena_destroy(ar);
}

static void test_arena_reset_allows_further_allocation(void) {
    Arena *ar = arena_create(8000);

    arena_alloc(ar, 4000, 8);
    arena_reset(ar);
    void *thing1 = arena_alloc(ar, 4001, 8);

    CHECK(thing1 != NULL);

    arena_destroy(ar);
}

static void test_arena_alloc_item_fits_exactly_returns_pointer(void) {
    Arena *ar = arena_create(16);

    void *thing1 = arena_alloc(ar, 16, 16);

    CHECK(thing1 != NULL);

    arena_destroy(ar);
}

static void test_arena_alloc_oddAlignment_returnsNullPointer(void) {
    Arena *ar = arena_create(16);

    void *thing1 = arena_alloc(ar, 16, 3);

    CHECK(thing1 == NULL);

    void *thing2 = arena_alloc(ar, 16, 0);

    CHECK(thing2 == NULL);

    void *thing3 = arena_alloc(ar, 16, 12);

    CHECK(thing3 == NULL);

    arena_destroy(ar);
}

int main(void) {
    test_arena_alloc_returns_correctly_aligned_pointers();
    test_arena_alloc_absurd_inputs_return_null();
    test_arena_alloc_exhausted_returns_null();
    test_arena_reset_allows_further_allocation();
    test_arena_alloc_item_fits_exactly_returns_pointer();
    test_arena_alloc_oddAlignment_returnsNullPointer();

    if (failures > 0) {
        return 1;
    }

    return 0;
}

