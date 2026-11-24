#include "vec.h"
#include "../../../lib/check.h"
#include "../../../lib/int_math.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void test_vec_push_pop_int(void) {
    size_t elem_size = sizeof(int);

    Vec *vec = vec_create(elem_size);

    CHECK(vec != NULL, "Failed to allocate Vec");

    for (int i = -500000; i < 500000; i++) 
    {
        if (!vec_push(vec, &i)) 
        {
            CHECK(((void)i, false), "Failed to push to Vec");
        }
    }

    for (int i = 499999; i > -500001; i--)
    {
        void *back;

        if (!vec_pop(vec, back))
        {
            CHECK(((void)back, false), "Failed to pop the last value from Vec");

            continue;
        }

        char *s = malloc(32);
        snprintf(s, 32, "back = %i, i = %i\n", *(int *)back, i);

        CHECK(*(int *)back == i, s);

        free(s);
    }
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
        CHECK(vec != NULL, "Failed to allocate Vec");
    }

    for (int i = -20, j = 20; i < 20; i++, j++) 
    {
        struct Widget widget = {
            .first = i,
            .last = j
        };

        if (!vec_push(vec, &widget)) 
        {
            CHECK(((void)i, false), "Failed to push to Vec");
        }
    }

    for (int i = 0, j = 40; i > -20; i--)
    {
        void *back;

        if (!vec_pop(vec, back))
        {
            CHECK(((void)back, false), "Failed to pop the last value from Vec");

            continue;
        }

        struct Widget *w_pointer = (struct Widget *)back;

        CHECK(w_pointer->first == i && w_pointer->last == j, "Popped widget does not match what was pushed.");
    }

    vec_destroy(vec);
}

void test_vec_get_pastTheEnd_returnsNull(void) {
    Vec *vec = vec_create(sizeof(int));

    if (vec == NULL) 
    {
        CHECK(vec != NULL, "Failed to allocate test vector");
        return;
    }

    int one = 1;

    if (!vec_push(vec, &one))
    {
        CHECK(false, "Failed to push 1");
    }

    int two = 2;

    if (!vec_push(vec, &two))
    {
        CHECK(false, "Failed to push 2");
    }

    int *three = vec_get(vec, 2);

    CHECK(three == NULL, "Three should be a null pointer, because there is no 2th element of the vector.");

    vec_destroy(vec);
}

void test_vec_pop_emptyVector_returnsFalse(void) {
    Vec *vec = vec_create(sizeof(int));

    if (vec == NULL)
    {
        CHECK(vec != NULL, "Failed to allocate test vector");
    }

    int *elem;

    if (vec_pop(vec, elem))
    {
        CHECK(false, "Popping an empty vector reported success.");
    }

    vec_destroy(vec);
}

void test_vec_whenCapacityExhausted_growsGeometrically(void) {
    Vec *vec = vec_create(sizeof(int));

    if (vec == NULL)
    {
        CHECK(false, "Failed to allocate Vector");
    }

    CHECK(vec_capacity(vec) == 64, "Initial capacity does not match expectation (64).");

    int elements[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

    for (short i = 0; i < 16; i++)
    {
        if (!vec_push(vec, &elements[i]))
        {
            CHECK(false, "Failed to push an element onto the vector");
        }
    }

    int seventeen = 17;

    if (!vec_push(vec, &seventeen))
    {
        CHECK(false, "Failed to push 17 onto the vector");
    }

    unsigned int capacity_after = vec_capacity(vec);

    CHECK(capacity_after == 64 + 32, "The capacity did not double after being exceeded.");
    CHECK(vec_len(vec) < vec_capacity(vec), "The vector length should never be longer than its capacity.");

    vec_destroy(vec);
}

void test_vec_create_

void test_vec_create_validCapacity_ReturnsPointerValidPointer(void) {
    size_t elem_size;

    if (!size_pow(2, 10, &elem_size)) 
    {
        elem_size = 16;
    }

    Vec *v = vec_create(elem_size);

    CHECK(v != NULL);

    vec_destroy(v);
}

void test_vec_create_invalidCapacity_ReturnsNull(void) {
    Vec *v = vec_create(SIZE_MAX);

    CHECK(v == NULL);

    if (v != NULL) vec_destroy(v);
}

void test_vec_len_whenNoElementsHaveBeenAdded_ReturnsZero(void) {
    size_t capacity;

    if (!size_pow(2, 10, &capacity)) 
    {
        capacity = 16;
    }

    Vec *v = vec_create(capacity);

    size_t len = vec_len(v);

    CHECK(len == 0);

    vec_destroy(v);
}

int main(void) {
    test_vec_create_validCapacity_ReturnsPointerValidPointer();
    test_vec_create_invalidCapacity_ReturnsNull();
    test_vec_len_whenNoElementsHaveBeenAdded_ReturnsZero();
}
