#include "map.h"
#include "../arena/arena.h"
#include <hash.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SLOT_SIZE 4

typedef struct MapEntry {
    char *key;
    int value;
} MapEntry;

typedef MapEntry Slot[SLOT_SIZE];

struct Map {
    size_t length;
    size_t dead;
    size_t capacity;
    union {
        MapEntry *entries;
        Slot *slots;
    };
};

static char TOMBSTONE = 0;
static char *TOMBSTONE_KEY = &TOMBSTONE;
static size_t initial_capacity = 16;

Map *map_create(void) {
    Map *new = malloc(sizeof(Map));

    if (new == NULL) return NULL;

    new->entries = calloc(initial_capacity, sizeof(Slot));

    if (new->entries == NULL) return NULL;

    return new;
}

void map_destroy(Map *m) {
    for (size_t i = 0; i < m->capacity; i++)
    {
        MapEntry entry = m->entries[i];

        if (entry.key != NULL && !strcmp(entry.key, TOMBSTONE_KEY))
        {
            free(entry.key);
        }
    }

    free(m->entries);
    free(m);
}

size_t map_len(const Map *m) {
    return m->length;
}

static bool slot_put(Map *m, Slot *slots, size_t capacity, MapEntry entry)
{
        int hash = string_hash_fnv1a(entry.key);
        size_t slot_index = hash & (capacity - 1);
        Slot slot = slots[slot_index];

        for (unsigned int s = 0; s < SLOT_SIZE; s++)
        {
            if (slot[s].key == NULL)
            {
                slot[s] = entry;

                if (m->slots == slots)
                {
                    m->length++;
                }
            }
            else if (slot[s].key == TOMBSTONE_KEY)
            {
                slot[s] = entry;
                m->dead--;                
            }
            else if (slot[s].key == entry.key)
            {
                slot[s].value = entry.value;
            }
        }

        return false;
}

static bool map_grow(Map *m) {
    if (!(SIZE_MAX / 2 > m->capacity)) return false;
    
    size_t new_capacity = m->capacity * 2;
    void *new_slots = calloc(new_capacity, sizeof(Slot));

    if (new_slots == NULL) return false;
    
    for (size_t e = 0; e < m->capacity * SLOT_SIZE; e++)
    {
        MapEntry entry = m->entries[e];

        if (entry.key == NULL) continue;
        if (!slot_put(m, new_slots, new_capacity, entry))
        {
            free(new_slots);

            return false;
        } 
    }

    m->capacity = new_capacity;
    m->slots = new_slots;
    m->dead = 0;

    return true;
}

bool map_put(Map *m, const char *key, int value) {
    size_t load = (double)(m->length + m->dead + 1)/m->capacity;

    if (load > 0.75f)
    {
        map_grow(m);
    }

    char *key_copy = strdup(key);
    
    if (!slot_put(m, m->slots, m->capacity, (MapEntry){ .key = key_copy, .value = value })) return false;

    return true;
}

static bool map_get_index(Map *m, const char *key, size_t *index) {
    uint64_t hash = string_hash_fnv1a(key);
    size_t slot_index = hash & (m->capacity - 1);
    Slot slot = m->slots[slot_index];

    for (unsigned int i = 0; i < SLOT_SIZE; i++)
    {
        MapEntry entry = slot[i];

        if (!strcmp(entry.key, key))
        {
            *index = slot_index * SLOT_SIZE + i;

            return true;
        }
    }

    return false;
}

bool map_get(const Map *m, const char *key, int *out) {
    size_t index;

    if (!map_get_index(m, key, &index)) return false;
    
    *out = m->entries[index].value;

    return true;
}

bool map_remove(Map *m, const char *key) {
    size_t index;

    if (!map_get_index(m, key, &index)) return false;

    MapEntry entry = m->entries[index];
    free(entry.key);
    entry.key = TOMBSTONE_KEY;
    m->dead++;

    return true;
}
