#include "STest.hpp"

STEST(FailExpectTrue) {
    EXPECT_TRUE(false);
}

STEST(PassExpectTrue) {
    EXPECT_TRUE(true);
}

STEST(FailExpectFalse) {
    EXPECT_FALSE(true);
}

STEST(PassExpectFalse) {
    EXPECT_FALSE(false);
}

STEST(FailExpectEq) {
    int a = 1, b = 2;
    EXPECT_EQ(a, b);
}

STEST(PassExpectEq) {
    int a = 1, b = 1;
    EXPECT_EQ(a, b);
}

STEST(PassExpectThrows) {
    EXPECT_THROWS(throw std::runtime_error{""}, std::runtime_error);
}

STEST(PassExpectThrowsAny) {
    EXPECT_THROWS_ANY(throw std::runtime_error{""});
}

STEST(FailExpectThrows) {
    EXPECT_THROWS(throw std::runtime_error{""}, std::bad_alloc);
}

STEST(FailExpectThrowsAny) {
    EXPECT_THROWS_ANY(0);
}

int main(int argc, const char* argv[]) {
    return static_cast<int>(RUN_STESTS(argc, argv));
}
