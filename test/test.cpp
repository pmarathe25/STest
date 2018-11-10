#include "interfaces/STest"
#include <cassert>

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

STEST(FailAssertTrue) {
    ASSERT_TRUE(false);
    assert(0); // This should not be reached.
}

STEST(PassAssertTrue) {
    ASSERT_TRUE(true);
}

STEST(FailAssertFalse) {
    ASSERT_FALSE(true);
    assert(0); // This should not be reached.
}

STEST(PassAssertFalse) {
    ASSERT_FALSE(false);
}

STEST(FailExpectEq) {
    int a = 1, b = 2;
    EXPECT_EQ(a, b);
}

STEST(PassExpectEq) {
    int a = 1, b = 1;
    EXPECT_EQ(a, b);
}

int main(int argc, char const *argv[]) {
    RUN_STESTS(argc, argv);
}
