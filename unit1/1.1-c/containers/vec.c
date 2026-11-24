#include "vec.h"
#include "stdlib.h"

struct Vec {
    size_t capacity;
    size_t len;
    size_t elem_size;
    char *buff;
};

Vec *vec_create(size_t elem_size) {
    Vec *new = malloc(sizeof(Vec));

    if (new == NULL) return NULL;

    new->capacity = 16;
    new->len = 0;
    new->elem_size = elem_size;
    new->buff = calloc(new->capacity, new->elem_size);

    if (new->buff == NULL) 
    {
        free(new);

        return NULL;
    }

    return new;
}
