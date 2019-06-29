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

int main(int argc, const char* argv[]) {
    return static_cast<int>(RUN_STESTS(argc, argv));
}
