#include "int_math.h"
#include "check.h"
#include <stdint.h>

void test_size_pow_small_operands(void) {
    size_t out = 0;

    bool success = size_pow(5, 9, &out);

    CHECK(success, "size_pow failed\n");
    CHECK(out == 1953125, "size_pow returned wrong value\n");
}

void test_size_pow_massiveBaseWithTinyExponent(void) {
    size_t out = 0;

    bool success = size_pow(2, 33, &out);

    CHECK(success, "size_pow failed\n");
    CHECK(out == 8589934592, "out did not equal 8589934592 as expected\n");
}

void test_size_pow_massiveEponentsOverflow(void) {
    size_t out = 0;

    bool success = size_pow(2, 64, &out);

    CHECK(!success, "size_pow should have failed\n");
    CHECK(out == SIZE_MAX, "out should equal SIZE_MAX\n");

    success = size_pow(2, 63, &out);

    CHECK(success, "size_pow should have succeeded\n");
    CHECK(out == 9223372036854775808ull, "out should have been equal to 9223372036854775808\n");
}

void test_size_pow_boundary(void) {
    size_t out = 0;

    bool success = size_pow(3, 40, &out);

    CHECK(success, "size_pow should have succeeded\n");
    CHECK(out == 12157665459056928801ull, "size_pow should have yielded 12157665459056928801\n");

    success = size_pow(3, 41, &out);

    CHECK(!success, "size_pow should not have succeeded\n");
    CHECK(out == SIZE_MAX, "size_pow should have yielded SIZE_MAX\n");
}

void test_size_pow_boundary_2(void) {
    size_t out = 0;

    bool success = size_pow(10, 19, &out);

    CHECK(success, "size_pow should have succeeded\n");
    CHECK(out == 10000000000000000000ull, "size_pow should have yielded 12157665459056928801\n");

    success = size_pow(10, 20, &out);

    CHECK(!success, "size_pow should not have succeeded\n");
    CHECK(out == SIZE_MAX, "size_pow should have yielded SIZE_MAX\n");
}

void test_size_pow_massiveBase_boundary(void) {
    size_t out = 0;

    bool success = size_pow(SIZE_MAX, 1, &out);

    CHECK(success, "size_pow should have succeeded\n");
    CHECK(out == SIZE_MAX, "size_pow should have yielded SIZE_MAX\n");

    success = size_pow(SIZE_MAX, 2, &out);

    CHECK(!success, "size_pow should not have succeeded\n");
    CHECK(out == SIZE_MAX, "size_pow should have yielded SIZE_MAX\n");
}

void test_size_pow_0and1bases_returnZerosAndOnes(void) {
    size_t out = 0;

    bool success = size_pow(0, 0, &out);

    CHECK(success, "size_pow should have succeeded.\n");
    CHECK(out == 1, "size_pow should have yielded 1.\n");

    success = size_pow(0, 5, &out);

    CHECK(success, "size_pow should have succeeded.\n");
    CHECK(out == 0, "size_pow should have yielded 0.\n");
}

int main(void) { 
    test_size_pow_small_operands();
    test_size_pow_massiveBaseWithTinyExponent();
    test_size_pow_massiveEponentsOverflow();
    test_size_pow_boundary();
    test_size_pow_boundary_2();
    test_size_pow_massiveBase_boundary();
    test_size_pow_0and1bases_returnZerosAndOnes();

    if (failures == 0) 
    {
        return 0;
    }

    return 1;
}
