#ifndef STEST_HPP
#define STEST_HPP
#include <SLog.hpp>
#include <functional>
#include <iostream>
#include <type_traits>
#include <typeinfo>

namespace {
    template <typename T, typename Stream, typename = void>
    struct is_streamable : std::false_type { };

    template <typename T, typename Stream>
    struct is_streamable<T, Stream, std::void_t<decltype(std::declval<Stream&>() << std::declval<T>())>> : std::true_type { };

    template <typename T, typename Stream>
    inline constexpr bool is_streamable_v = is_streamable<T, Stream>::value;

    // Catch-all stream overload for types without an overload.
    template <typename T, std::enable_if_t<!is_streamable_v<const T&, std::ostream&>, int> = 0>
    inline std::ostream& operator<<(std::ostream& os, const T& t) {
        const char* ptr = reinterpret_cast<const char*>(&t);

        for (size_t i = 0; i < sizeof(T); ++i) {
            os << (i == 0 ? "(raw bytes) 0x" : "") << std::hex << +ptr[i];
        }
        return os;
    }
}

namespace Stealth::Test {
    auto& STEST_ERROR_STREAM = std::cerr;

    // Defining tests
    using TestFunc = std::function<void(void)>;
    bool addTest(TestFunc func, const std::string& name);

    class TestFailedException { };

    // Tests
    #define STEST(NAME) \
        void NAME(); \
        namespace { \
            [[maybe_unused]] const bool _ST_Func_Result_##NAME##_##discard = Stealth::Test::addTest(NAME, __FILE__ ":" #NAME); \
        } \
        void NAME()

    // Fixtures
    #define STEST_F(FIXTURE_CLASS, NAME) \
        namespace { \
            class FIXTURE_CLASS##_stest_derived_##NAME##_class : public FIXTURE_CLASS { \
            public: \
                void __stest_run_func(); \
            } FIXTURE_CLASS##_stest_derived_##NAME##_instance; \
            [[maybe_unused]] const bool _ST_Func_Result_##NAME##_##discard = Stealth::Test::addTest( \
                std::bind(&FIXTURE_CLASS##_stest_derived_##NAME##_class::__stest_run_func, \
                    &FIXTURE_CLASS##_stest_derived_##NAME##_instance), __FILE__ ":" #NAME); \
        } \
        void FIXTURE_CLASS##_stest_derived_##NAME##_class::__stest_run_func()

    // Checks
    #define _LOG_STEST_ERROR(MESSAGE) Stealth::Test::STEST_ERROR_STREAM << "\033[1;31m[   FAILURE]\n\t" << MESSAGE << "\033[0m" << std::endl
    #define _LOG_STEST_MISMATCH(EXPECTED, VALUE) _LOG_STEST_ERROR("At " << __FILE__ << ":" << __LINE__ << ", " << "Value of: " << #VALUE << "\n\t  Actual: " << (VALUE) << "\n\tExpected: " << (EXPECTED))

    #define EXPECT_EQ(VALUE, EXPECTED) if (!(EXPECTED == VALUE)) { _LOG_STEST_MISMATCH(EXPECTED, VALUE); throw Stealth::Test::TestFailedException{}; }
    #define EXPECT_TRUE(CONDITION) EXPECT_EQ(CONDITION, true)
    #define EXPECT_FALSE(CONDITION) EXPECT_EQ(CONDITION, false)

    #define EXPECT_THROWS(STATEMENT, EXCEPTION_TYPE) \
        { \
            bool __stest_exception_caught{false}; \
            try { \
                (void) (STATEMENT); \
                _LOG_STEST_ERROR("Expected exception of type: " << #EXCEPTION_TYPE << ", but no exception was thrown"); \
            } catch (const EXCEPTION_TYPE& __stest_exception) { \
                __stest_exception_caught = true; \
            } catch (const std::exception& __stest_exception) { \
                _LOG_STEST_ERROR("Expected exception of type: " << #EXCEPTION_TYPE << ", but received exception of type: " << typeid(__stest_exception).name()); \
            } \
            if (!__stest_exception_caught) { throw Stealth::Test::TestFailedException{}; } \
        }

    #define EXPECT_THROWS_ANY(STATEMENT) \
        { \
            try { \
                (void) (STATEMENT); \
                _LOG_STEST_ERROR("Expected exception, but no exception was thrown"); \
                throw Stealth::Test::TestFailedException{}; \
            } catch (const std::exception& __stest_exception) { } \
        }

    // Running tests
    enum class Status : int {
        OK = 0,
        FAIL = 1,
    };

    Status runTests(int argc, const char* argv[], const std::string& filename);

    #define RUN_STESTS(argc, argv) Stealth::Test::runTests(argc, argv, __FILE__)

    #define STEST_MAIN() \
        int main(int argc, const char* argv[]) { \
            return static_cast<int>(RUN_STESTS(argc, argv)); \
        }
} // Stealth::Test

#endif // include guard
