#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Stealth::Test {
    struct TestCase {
        TestCase(std::function<void()> func, std::string name) : func{std::move(func)}, name{std::move(name)} { }
        void operator()() const { func(); }
        // Data
        const std::function<void()> func;
        const std::string name;
    };

    // Container for all test cases.
    static std::map<std::string, std::vector<TestCase>> allTests{};

    struct Emplacer {
        Emplacer(std::function<void()> func, std::string testName, std::string testCaseName) {
            // Construct test cases in place.
            allTests[testName].emplace_back(func, testCaseName);
        }
    };

    // Default behavior is to print test case name and then run the test.
    constexpr auto defaultRun = [](const std::string& testName, const TestCase& testCase){ std::cout << "&&&& RUNNING " << testName << "::" << testCase.name << std::endl; testCase(); };

    inline void runTests(const std::function<void(const std::string&, const TestCase&)>& runTestCase = defaultRun) {
        for (const auto& test : allTests)
            for (const auto& testCase : test.second)
                runTestCase(test.first, testCase);
    }

    // Test Case Helpers
    #define TEST_CASE_NAME(testName, testCaseName) testName##_##testCaseName
    #define EMPLACER_INSTANCE_NAMESPACE(testName, testCaseName) Stealth::Test::EmplacerInstance_##name##_##testCaseName
    // Test Cases
    #define TEST(testName, testCaseName) \
    void TEST_CASE_NAME(testName, testCaseName)(); \
    namespace EMPLACER_INSTANCE_NAMESPACE(testName, testCaseName) { \
        static Emplacer instance{TEST_CASE_NAME(testName, testCaseName), #testName, #testCaseName}; \
    } /* End namespace */ \
    void TEST_CASE_NAME(testName, testCaseName)()

} /* Stealth::Test */
