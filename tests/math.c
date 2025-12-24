#include <unity.h>

// Setup (called before each test)
void setUp(void) {
}

// Teardown (called after each test)
void tearDown(void) {
}

// Actual Test Function
void test_addition_should_work(void) {
    TEST_ASSERT_EQUAL_INT(5, 2 + 3);
}

void test_subtraction_should_work(void) {
    TEST_ASSERT_EQUAL_INT(10, 20 - 10);
}

// Main Test Runner
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addition_should_work);
    RUN_TEST(test_subtraction_should_work);
    return UNITY_END();
}
