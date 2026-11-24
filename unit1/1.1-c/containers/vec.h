#ifndef DYNAMIC_VECTOR
#define DYNAMIC_VECTOR
#include <stddef.h>
#include <stdbool.h>

typedef struct Vec Vec;

Vec     *vec_create(size_t elem_size);
void    vec_destroy(Vec *v);
size_t  vec_capacity(const Vec *v);
size_t  vec_len(const Vec *v);
void    *vec_get(Vec *v, size_t i);
bool    vec_push(Vec *v, const void *elem);
bool    vec_pop(Vec *v, void *out);

#endif
