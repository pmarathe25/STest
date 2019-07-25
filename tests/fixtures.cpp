#include "STest/include/STest.hpp"

class TestFixture {
protected:
    int a{0}, b{0}, c{0};
};

STEST_F(TestFixture, ValuesInitialized) {
    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 0);
    EXPECT_EQ(c, 0);
}

namespace testNamespace {
    STEST_F(TestFixture, NamespaceValuesInitialized) {
        EXPECT_EQ(a, 0);
        EXPECT_EQ(b, 0);
        EXPECT_EQ(c, 0);
    }
} // testNamespace


STEST_F(TestFixture, CanModifyValues) {
    a = 1;
    EXPECT_EQ(a, 1);
    b = 2;
    EXPECT_EQ(b, 2);
    c = 3;
    EXPECT_EQ(c, 3);
}

STEST_MAIN();
