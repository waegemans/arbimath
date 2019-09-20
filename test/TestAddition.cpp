#include "arbimath/bigint/BigInt.hpp"

#include <gtest/gtest.h>

TEST(TestAddition, Simple) {
    arbimath::BigInt a(1);
    arbimath::BigInt b(2);
    arbimath::BigInt c(3);

    EXPECT_EQ(a+b,c);
    EXPECT_NE(a+b,-c);
    EXPECT_EQ((-a)+(-b),-c);
    EXPECT_NE((-a)+(-b),c);
}

TEST(TestAddition, SimpleZero) {
    arbimath::BigInt a(1);
    arbimath::BigInt b(0xffffffffffffffffull);
    arbimath::BigInt c(42);
    arbimath::BigInt zero(0);

    EXPECT_EQ(a+zero,a);
    EXPECT_EQ(b+zero,b);
    EXPECT_EQ(c+zero,c);
}

TEST(TestAddition, SimpleOverflow) {
    arbimath::BigInt a(0xffffffffffffffffull);
    arbimath::BigInt b(1);
    arbimath::BigInt c(0x0fffffffffffffffull);
    arbimath::BigInt d(0xf000000000000001ull);

    EXPECT_EQ(a+b,c+d);
}

TEST(TestAddition, SimpleOverflow2) {
    arbimath::BigInt a(0xffffffffffffffffull);
    arbimath::BigInt b(1);
    arbimath::BigInt c("0x1ffffffffffffffff");

    EXPECT_EQ(a+a+b,c);
}

TEST(TestAddition, MixedSign) {
    arbimath::BigInt a("0x2");
    arbimath::BigInt b("-0x3");
    arbimath::BigInt c("-0x1");

    EXPECT_EQ(a+b,c);
    EXPECT_EQ(b+a,c);
}

TEST(TestAddition, MixedSign2) {
    arbimath::BigInt a("-0x2");
    arbimath::BigInt b("0x3");
    arbimath::BigInt c("0x1");

    EXPECT_EQ(a+b,c);
    EXPECT_EQ(b+a,c);
}

TEST(TestAddition, MixedSignBorrow) {
    arbimath::BigInt a("0xfa0000000000000000");
    arbimath::BigInt b("-0x1");
    arbimath::BigInt c("0xf9ffffffffffffffff");

    EXPECT_EQ(a+b,c);
    EXPECT_EQ(b+a,c);
}