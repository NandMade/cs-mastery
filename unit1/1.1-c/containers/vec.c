#include "vec.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef unsigned char byte;

struct Vec {
    size_t capacity;
    size_t len;
    size_t elem_size;
    byte *buff;
};

static const size_t initial_capacity = 16;

Vec *vec_create(size_t elem_size) {
    if (elem_size == 0) return NULL;
    if (SIZE_MAX / initial_capacity < elem_size) return NULL;

    byte *buff = calloc(initial_capacity, elem_size);
    
    if (buff == NULL) return NULL;
    
    Vec *new = malloc(sizeof(Vec));

    if (new == NULL) 
    {
        free(buff);

        return NULL;
    }

    new->capacity = initial_capacity;
    new->len = 0;
    new->elem_size = elem_size;
    new->buff = buff;

    return new;
}

void vec_destroy(Vec *v) {
    free(v->buff);
    free(v);
}

size_t vec_capacity(const Vec *v) {
    return v->capacity;
}

size_t vec_len(const Vec *v) {
    return v->len;
}

void *vec_get(Vec *v, size_t i) {
    if (i >= v->len) return NULL;

    return v->buff + i * v->elem_size;
}

static bool vec_grow(Vec *v) {
    if (SIZE_MAX / v->capacity / v->elem_size < 1.5) {
        return false;
    }

    size_t new_capacity = v->capacity + v->capacity / 2;
    byte *newbuff = realloc(v->buff, new_capacity * v->elem_size);

    if (newbuff == NULL) 
    {
        return false;
    }
    
    v->capacity = new_capacity;
    v->buff = newbuff;

    return true;
}

bool vec_push(Vec *v, const void *elem) {
    if (v->len == v->capacity) {
        bool grew = vec_grow(v);

        if (!grew) return false;
    }

    memcpy(v->buff + v->len * v->elem_size, elem, v->elem_size);
    v->len++;

    return true;
}

bool vec_pop(Vec *v, void *out) {
    if (v->len == 0) {
        return false;
    }

    memcpy(out, v->buff + (v->len - 1) * v->elem_size, v->elem_size);

    v->len--;

    return true;
}