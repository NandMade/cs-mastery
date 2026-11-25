#include "vec.h"
#include "../../../lib/check.h"
#include "../../../lib/int_math.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void test_vec_push_pop_int(void) {
    size_t elem_size = sizeof(int);

    Vec *vec = vec_create(elem_size);

    CHECK(vec != NULL, "Failed to allocate Vec.\n");

    for (int i = -500000; i < 500000; i++) 
    {
        if (!vec_push(vec, &i)) 
        {
            CHECK(((void)i, false), "Failed to push to Vec.\n");
        }
    }

    for (int i = 499999; i > -500001; i--)
    {
        int back;

        if (!vec_pop(vec, &back))
        {
            CHECK(((void)back, false), "Failed to pop the last value from Vec.\n");

            continue;
        }

        char *s = malloc(32);
        snprintf(s, 32, "back = %i, i = %i\n", back, i);

        CHECK(back == i, s);

        free(s);
    }

    vec_destroy(vec);
}

struct Widget {
    int first;
    int last;
};

void test_vec_push_pop_struct(void) {
    size_t elem_size = sizeof(struct Widget);

    Vec *vec = vec_create(elem_size);

    if (vec == NULL) 
    {
        CHECK(vec != NULL, "Failed to allocate Vec.\n");
    }

    for (int i = -20, j = 20; i < 20; i++, j++) 
    {
        struct Widget widget = {
            .first = i,
            .last = j
        };

        if (!vec_push(vec, &widget)) 
        {
            CHECK(((void)i, false), "Failed to push to Vec.\n");
        }
    }

    for (int i = 19, j = 59; i >= -20; i--, j--)
    {
        struct Widget back;

        if (!vec_pop(vec, &back))
        {
            CHECK(((void)back, false), "Failed to pop the last value from Vec.\n");

            continue;
        }

        char *s = malloc(1024);

        snprintf(s, 1024, "Expected { first: %i, last: %i }, Actual { first: %i, last: %i }\n", i, j, back.first, back.last);

        CHECK(back.first == i && back.last == j, s);

        free(s);
    }

    vec_destroy(vec);
}

void test_vec_get_pastTheEnd_returnsNull(void) {
    Vec *vec = vec_create(sizeof(int));

    if (vec == NULL) 
    {
        CHECK(vec != NULL, "Failed to allocate test vector.\n");
        return;
    }

    int one = 1;

    if (!vec_push(vec, &one))
    {
        CHECK(false, "Failed to push 1.\n");
    }

    int two = 2;

    if (!vec_push(vec, &two))
    {
        CHECK(false, "Failed to push 2.\n");
    }

    int *three = vec_get(vec, 2);

    CHECK(three == NULL, "Three should be a null pointer, because there is no 2th element of the vector.\n");

    vec_destroy(vec);
}

void test_vec_pop_emptyVector_returnsFalse(void) {
    Vec *vec = vec_create(sizeof(int));

    if (vec == NULL)
    {
        CHECK(vec != NULL, "Failed to allocate test vector.\n");
    }

    int elem;

    if (vec_pop(vec, &elem))
    {
        CHECK(false, "Popping an empty vector reported success.\n");
    }

    vec_destroy(vec);
}

void test_vec_whenCapacityExhausted_growsGeometrically(void) {
    Vec *vec = vec_create(sizeof(int));

    if (vec == NULL)
    {
        CHECK(false, "Failed to allocate Vector.\n");
    }

    CHECK(vec_capacity(vec) == 16, "Initial capacity does not match expectation (16).\n");

    int elements[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

    for (short i = 0; i < 16; i++)
    {
        if (!vec_push(vec, &elements[i]))
        {
            CHECK(false, "Failed to push an element onto the vector.\n");
        }
    }

    CHECK(vec_capacity(vec) == 16, "Should still have a capacity of 16.\n");

    int seventeen = 17;

    if (!vec_push(vec, &seventeen))
    {
        CHECK(false, "Failed to push 17 onto the vector.\n");
    }

    unsigned int capacity_after = vec_capacity(vec);

    CHECK(capacity_after == 16 + 8, "The capacity did not double after being exceeded.\n");
    CHECK(vec_len(vec) < vec_capacity(vec), "The vector length should never be longer than its capacity.\n");

    vec_destroy(vec);
}

void test_vec_create_valid_elem_size_ReturnsPointerValidPointer(void) {
    size_t elem_size;

    if (!size_pow(2, 10, &elem_size)) 
    {
        elem_size = 16;
    }

    Vec *v = vec_create(elem_size);

    CHECK(v != NULL, "Failed to allocate vector.\n");

    vec_destroy(v);
}

void test_vec_create_invalid_elem_size_ReturnsNull(void) {
    Vec *v = vec_create(SIZE_MAX);

    CHECK(v == NULL, "Should have failed to allocate vector.\n");

    if (v != NULL) vec_destroy(v);
}

void test_vec_len_whenNoElementsHaveBeenAdded_ReturnsZero(void) {
    Vec *v = vec_create(sizeof(int));

    size_t len = vec_len(v);

    CHECK(len == 0, "len should be zero for a newly initialized vector.\n");

    vec_destroy(v);
}

void test_vec_impossible_elem_size_returnsNull(void) {
    Vec *v = vec_create(SIZE_MAX / 2);

    CHECK(v == NULL, "Should have failed to allocate Vec.\n");

    vec_destroy(v);
}

int main(void) {
    test_vec_push_pop_int();
    test_vec_push_pop_struct();
    test_vec_get_pastTheEnd_returnsNull();
    test_vec_pop_emptyVector_returnsFalse();
    test_vec_whenCapacityExhausted_growsGeometrically();
    test_vec_create_valid_elem_size_ReturnsPointerValidPointer();
    test_vec_create_invalid_elem_size_ReturnsNull();
    test_vec_len_whenNoElementsHaveBeenAdded_ReturnsZero();
}
