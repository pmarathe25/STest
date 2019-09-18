#include "STest/include/STest.hpp"

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

STEST(PassExpectThrowsTwice) {
    EXPECT_THROWS(throw std::runtime_error{""}, std::runtime_error);
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

STEST(PassCanCompareTypeIDs) {
    EXPECT_EQ(typeid(0), typeid(0));
}

STEST(FailCanCompareTypeIDs) {
    EXPECT_EQ(typeid(0.f), typeid(0));
}

void helperPass() {
    EXPECT_EQ(0, 0);
}

STEST(PassCanUseHelper) {
    helperPass();
}

void helperFail() {
    EXPECT_EQ(1, 0);
}

STEST(FailCanUseHelper) {
    helperFail();
}

void helperThrowsPass() {
    EXPECT_THROWS(throw std::runtime_error{""}, std::runtime_error);
}

STEST(PassCanUseHelperThrows) {
    helperThrowsPass();
}

void helperThrowsFail() {
    EXPECT_THROWS(throw std::runtime_error{""}, std::bad_alloc);
}

STEST(FailCanUseHelperThrows) {
    helperThrowsFail();
}

struct DefinitelyNotStreamable {
    constexpr bool operator==(const DefinitelyNotStreamable& other) const {
        return mVal == other.mVal;
    }

    int mVal{0};
};

STEST(PassCanDisplayCustomType) {
    EXPECT_EQ(DefinitelyNotStreamable{}, DefinitelyNotStreamable{});
}

STEST(FailCanDisplayCustomType) {
    EXPECT_EQ(DefinitelyNotStreamable{1}, DefinitelyNotStreamable{0});
}

STEST_MAIN();
