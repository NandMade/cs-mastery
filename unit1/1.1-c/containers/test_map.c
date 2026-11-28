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

    map_destroy(m);
}

Map *build_large_map(void) {
    Map *m = map_create();

    CHECK(m != NULL, "Failed to allocate Map.\n");

    for (int i = 0; i < 100000; i++)
    {
        char key[9];
        snprintf(key, 9, "key%i", i);
        bool success = map_put(m, key, i);
        CHECK(success, "Failed to put value in Map.\n");
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
        snprintf(key, 9, "key%i", i);
        bool success = map_get(m, key, &out);
        CHECK(success, "Failed to get value from Map\n");   
        CHECK(out == i, "The value does not match what was put in for the key.\n");
    }

    map_destroy(m);
}

void test_map_remove_removeEveryOtherKeyFrom100000Push_consistencyIsMaintained(void) {
    Map *m = build_large_map();

    for (int i = 0; i < 100000; i += 2) 
    {
        if (i % 2 == 0)
        {
            char s[9];
            snprintf(s, 9, "key%i", i);
            CHECK(map_remove(m, s), "Failed to remove entry from map.\n");
        }
    }

    for (int i = 0; i < 100000; i++)
    {
        if (i % 2 == 0) 
        {
            char s[9];
            snprintf(s, 9, "key%i", i);
            CHECK(!map_remove(m, s), "Removed key is still present.\n");
        }
        else 
        {
            char s[9];
            int out;
            snprintf(s, 9, "key%i", i);
            CHECK(map_get(m, s, &out), "Key should still have been present.\n");
            CHECK(out == i, "Retrieved value does not match what was originally pushed.\n");
        }
    }

    map_destroy(m);
}

void test_map_push_keysAreCopied(void) {
    Map *m = map_create();

    CHECK(m != NULL, "Failed to allocate Map.\n");

    char key[] = "key1";

    CHECK(map_put(m, key, 1), "Failed to push entry.\n");

    key[0] = 'c';
    int out;

    CHECK(map_get(m, "key1", &out), "Failed to get entry after key was modified.\n");
    CHECK(out == 1, "Retrieved entry value does not match original value put.\n");

    map_destroy(m);
}

int main(void) {
    test_map_put_newKey_addsEntry();
    test_map_get_returnsMatchingEntry();
    test_map_get_keyDoesNotExist_returnsFalse();
    test_map_put_keyAlreadyExists_overwritesValue();
    test_map_remove_keyDoesNotExist_returnsFalse();
    test_map_put_100000Entries_growsCorrectly();
    test_map_remove_removeEveryOtherKeyFrom100000Push_consistencyIsMaintained();
    test_map_push_keysAreCopied();

    if (failures > 0)
    {
        return 1;
    }

    return 0;
}