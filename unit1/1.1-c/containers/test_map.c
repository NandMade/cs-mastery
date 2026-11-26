#include "map.h"
#include <check.h>

void test_map_put_newKey_addsEntry(void) {
    Map *m = map_create();

    CHECK(m != NULL, "Failed to allocate Map\n");
    CHECK(map_put(m, "one", 1), "Failed to add one\n");
    CHECK(map_len(m) == 1, "Map length does not match number of added elements.\n");

    map_destroy(m);
}

void test_map_get_returnsMatchingEntry(void) {
    Map *m = map_create();

    CHECK(m != NULL, "Failed to allocate Map.\n");
    CHECK(map_put(m, "one", 1), "Failed to add one\n");

    int out;
    bool success = map_get(m, "one", &out);

    CHECK(success, "Failed to get one\n");

    if (success)
    {
        CHECK(out == 1, "Retrieved value did not match put value.\n");
    }

    map_destroy(m);
}

void test_map_get_keyDoesNotExist_returnsFalse(void) {
    Map *m = map_create();

    CHECK(m != NULL, "Failed to allocate Map.\n");
    map_put(m, "one", 1);
    map_put(m, "two", 2);

    int out;

    bool success = map_get(m, "three", &out);

    CHECK(!success, "Should not have succeeded in getting non-existent key.");

    map_destroy(m);
}

void test_map_put_keyAlreadyExists_overwritesValue(void) {
    Map *m = map_create();

    CHECK(m != NULL, "Failed to allocate Map.\n");
    map_put(m, "one", 1);
    map_put(m, "two", 2);

    bool success = map_put(m, "two", 4);

    CHECK(success, "Failed to put two in Map.\n");
    CHECK(map_len(m) == 2, "Length should be 2.\n");

    map_destroy(m);
}

void test_map_remove_keyDoesNotExist_returnsFalse(void) {
    Map *m = map_create();

    CHECK(m != NULL, "Failed to allocate Map.\n");
    map_put(m, "one", 1);
    map_put(m, "two", 2);

    bool success = map_remove(m, "three");

    CHECK(!success, "Map somehow succeeded in removing non-existent key.\n");

    map_destry(m);
}

Map *build_large_map(void) {
    Map *m = map_create();

    CHECK(m != NULL, "Failed to allocate Map.\n");

    for (int i = 0; i < 100000; i++)
    {
        char key[9];

        CHECK(map_put(m, snprintf(key, 9, "key%i", i), i), "Failed to put value in Map.\n");
    }

    return m;
}

void test_map_put_100000Entries_growsCorrectly(void) {
    Map *m = build_large_map();

    CHECK(m != NULL, "Failed to allocate Map.\n");

    for (int i = 0; i < 100000; i++)
    {
        char key[9];
        int out;

        CHECK(map_get(m, snprintf(key, 9, "key%i", i), &out), "Failed to get value from Map.\n");   
        CHECK(out == i, "The value does not match what was put in for the key.\n");
    }

    map_destroy(m);
}

int main(void) {
    test_map_put_newKey_addsEntry();
    test_map_get_returnsMatchingEntry();
    test_map_get_keyDoesNotExist_returnsFalse();
    test_map_put_keyAlreadyExists_overwritesValue();
    test_map_remove_keyDoesNotExist_returnsFalse();
    test_map_put_100000Entries_growsCorrectly();

    if (failures > 0)
    {
        return 1;
    }

    return 0;
}