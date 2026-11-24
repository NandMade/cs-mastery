#include "int_math.h"
#include "check.h"

void test_size_pow_small_operands(void) {
    size_t *out;

    bool success = size_pow(5, 9, out);

    CHECK(success);
    CHECK(*out == 1953125);
}

int main(void) { 
    test_size_pow_small_operands();

    if (failures == 0) 
    {
        return 0;
    }

    return 1;
}
