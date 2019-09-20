#include "arbimath/bigint/BigInt.hpp"

#include <gtest/gtest.h>

TEST(TestConstructor, ZeroConstructor) {
    arbimath::BigInt a;
    arbimath::BigInt b(0);
    arbimath::BigInt c("0x0000");
    arbimath::BigInt d("0x0");

    EXPECT_EQ(a,b);
    EXPECT_EQ(a,c);
    EXPECT_EQ(a,d);
    EXPECT_EQ(b,c);
    EXPECT_EQ(b,d);
    EXPECT_EQ(c,d);
}

TEST(TestConstructor, HexConstructor) {
    arbimath::BigInt a (0xffffffffffffffffull);
    arbimath::BigInt b ("0xffffffffffffffff");
    arbimath::BigInt c ("-0xffffffffffffffff");
    arbimath::BigInt d (-a);

    EXPECT_EQ(a,b);
    EXPECT_NE(a,c);
    EXPECT_NE(a,d);
    EXPECT_NE(b,c);
    EXPECT_NE(b,d);
    EXPECT_EQ(c,d);
}
