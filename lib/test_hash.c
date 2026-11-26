#include "hash.h"
#include "check.h"

void test_hash_fnv1a_Hello_World_returns_8c0ee9d1fb9ea645(void) {
    CHECK(hash_fnv1a((byte *)"Hello World", sizeof("Hello World")) == 0x8c0ee9d1fb9ea645, "Should have produced a hash of 0x8c0ee9d1fb9ea645\n");
}

int main(void) {
    test_hash_fnv1a_Hello_World_returns_8c0ee9d1fb9ea645();

    if (failures > 0) 
    {
        return 1;
    }

    return 0;
}