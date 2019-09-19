#include "arbimath/bigint/BigInt.hpp"

#include <gtest/gtest.h>

TEST(TestConstructor, DefaultConstructor) {
    arbimath::BigInt a;
    arbimath::BigInt b(0);

    EXPECT_EQ(a,b);
}
