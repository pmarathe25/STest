#pragma once
#include <Stealth/SLog.hpp>
#include <functional>
#include <iostream>
#include <typeinfo>

namespace Stealth::Test {
    // Defining tests
    using TestFunc = std::function<void(bool&)>;
    bool addTest(TestFunc func, const std::string& name);

    // Tests
    #define STEST(NAME) \
        void NAME(bool& __stest_passed); \
        namespace { \
            [[maybe_unused]] const bool _ST_Func_Result_##NAME##_##discard = Stealth::Test::addTest(NAME, __FILE__ ":" #NAME); \
        } \
        void NAME(bool& __stest_passed)

    // Fixtures
    #define STEST_F(FIXTURE_CLASS, NAME) \
        namespace { \
            class _stest_derived_##FIXTURE_CLASS##_##NAME##_class : public FIXTURE_CLASS { \
            public: \
                void __stest_run_func(bool& __stest_passed); \
            } _stest_derived_##FIXTURE_CLASS##_##NAME##_instance; \
            [[maybe_unused]] const bool _ST_Func_Result_##NAME##_##discard = Stealth::Test::addTest( \
                std::bind(&_stest_derived_##FIXTURE_CLASS##_##NAME##_class::__stest_run_func, \
                    &_stest_derived_##FIXTURE_CLASS##_##NAME##_instance, std::placeholders::_1), __FILE__ ":" #NAME); \
        } \
        void ::_stest_derived_##FIXTURE_CLASS##_##NAME##_class::__stest_run_func(bool& __stest_passed)

    // Checks
    #define _LOG_STEST_ERROR(MESSAGE) std::cerr << "\033[1;31m[     ERROR]\n\t" << MESSAGE << "\033[0m" << std::endl
    #define _LOG_STEST_MISMATCH(EXPECTED, VALUE) _LOG_STEST_ERROR("At " << __FILE__ << ":" << __LINE__ << ", " << "Value of: " << #VALUE << "\n\t  Actual: " << (VALUE) << "\n\tExpected: " << (EXPECTED))

    #define EXPECT_EQ(VALUE, EXPECTED) if (!(EXPECTED == VALUE)) { _LOG_STEST_MISMATCH(EXPECTED, VALUE); __stest_passed = false; }
    #define EXPECT_TRUE(CONDITION) EXPECT_EQ(CONDITION, true)
    #define EXPECT_FALSE(CONDITION) EXPECT_EQ(CONDITION, false)

    #define EXPECT_THROWS(STATEMENT, EXCEPTION_TYPE) bool __stest_exception_caught{false}; \
        try { { (STATEMENT); } _LOG_STEST_ERROR("Expected exception of type: " << #EXCEPTION_TYPE << ", but no exception was thrown"); } \
        catch (const EXCEPTION_TYPE& __stest_exception) { __stest_exception_caught = true; } \
        catch (const std::exception& __stest_exception) { _LOG_STEST_ERROR("Expected exception of type: " << #EXCEPTION_TYPE << ", but received exception of type: " << typeid(__stest_exception).name()); } \
        if (!__stest_exception_caught) { __stest_passed = false; }
    #define EXPECT_THROWS_ANY(STATEMENT) EXPECT_THROWS(STATEMENT, std::exception)

    // Running tests
    enum class Status : int {
        OK = 0,
        FAIL = 1,
    };

    Status runTests(int argc, const char* argv[], const std::string& filename);

    #define RUN_STESTS(argc, argv) Stealth::Test::runTests(argc, argv, __FILE__)
} // Stealth::Test
