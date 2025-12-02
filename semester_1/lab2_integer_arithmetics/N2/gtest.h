#pragma once
#include <iostream>
#include <string>
#include <vector>

class TestRegistry {
private:
    struct TestCase {
        std::string suite;
        std::string name;
        void (*func)();
        bool failed;
        std::string error_msg;
    };

    std::vector<TestCase> tests;
    static TestRegistry* instance;

    TestRegistry() = default;

public:
    static TestRegistry& get() {
        if (!instance) instance = new TestRegistry();
        return *instance;
    }

    void add_test(const std::string& suite, const std::string& name, void (*func)()) {
        tests.push_back({ suite, name, func, false, "" });
    }

    void set_failed(const std::string& msg) {
        if (!tests.empty()) {
            tests.back().failed = true;
            tests.back().error_msg = msg;
        }
    }

    int run_all() {
        std::cout << "[==========] Running " << tests.size() << " tests\n";
        int passed = 0;

        for (auto& test : tests) {
            test.failed = false;
            test.error_msg = "";

            std::cout << "[ RUN      ] " << test.suite << "." << test.name << "\n";

            try {
                test.func();
            }
            catch (const std::exception& e) {
                test.failed = true;
                test.error_msg = "Exception: " + std::string(e.what());
            }
            catch (...) {
                test.failed = true;
                test.error_msg = "Unknown exception";
            }

            if (!test.failed) {
                std::cout << "[       OK ] " << test.suite << "." << test.name << "\n";
                passed++;
            }
            else {
                std::cout << "[  FAILED  ] " << test.suite << "." << test.name;
                if (!test.error_msg.empty()) {
                    std::cout << " - " << test.error_msg;
                }
                std::cout << "\n";
            }
        }

        std::cout << "[==========] " << passed << "/" << tests.size() << " tests passed\n";
        return (tests.size() - passed);
    }
};

TestRegistry* TestRegistry::instance = nullptr;

#define TEST(test_suite_name, test_name) \
    void test_suite_name##_##test_name(); \
    struct test_suite_name##_##test_name##_Register { \
        test_suite_name##_##test_name##_Register() { \
            TestRegistry::get().add_test(#test_suite_name, #test_name, \
                &test_suite_name##_##test_name); \
        } \
    } test_suite_name##_##test_name##_instance; \
    void test_suite_name##_##test_name()

#define EXPECT_EQ(val1, val2) \
    do { \
        auto v1 = (val1); \
        auto v2 = (val2); \
        if (v1 != v2) { \
            TestRegistry::get().set_failed(std::string(#val1 " != " #val2) + \
                " (" + std::to_string(v1) + " vs " + std::to_string(v2) + ")"); \
            return; \
        } \
    } while (0)

#define EXPECT_TRUE(cond) \
    do { \
        if (!(cond)) { \
            TestRegistry::get().set_failed(#cond " is false"); \
            return; \
        } \
    } while (0)

#define EXPECT_FALSE(cond) \
    do { \
        if (cond) { \
            TestRegistry::get().set_failed(#cond " is true"); \
            return; \
        } \
    } while (0)

#define EXPECT_NE(val1, val2) \
    do { \
        auto v1 = (val1); \
        auto v2 = (val2); \
        if (v1 == v2) { \
            TestRegistry::get().set_failed(std::string(#val1 " == " #val2) + \
                " (" + std::to_string(v1) + ")"); \
            return; \
        } \
    } while (0)

#define ASSERT_EQ(val1, val2) EXPECT_EQ(val1, val2)
#define ASSERT_TRUE(cond) EXPECT_TRUE(cond)
#define ASSERT_FALSE(cond) EXPECT_FALSE(cond)

int main(int argc, char** argv) {
    return TestRegistry::get().run_all();
}