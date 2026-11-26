#include <stddef.h>
#include <stdbool.h>

typedef struct Map Map;
Map   *map_create(void);
void   map_destroy(Map *m);
size_t map_len(const Map *m);
bool   map_put(Map *m, const char *key, int value);  /* copies key; overwrites an existing key's value; false on failure */
bool   map_get(const Map *m, const char *key, int *out);
bool   map_remove(Map *m, const char *key);          /* false if key not present */