#include <unity.h>

#include "../src/common.h"

#define EXPECTED_COUNT 4
#define LIST(X)                                                                \
  X(ONE)                                                                       \
  X(TWO)                                                                       \
  X(THREE)                                                                     \
  X(FOUR)
#define LIST_COUNT (0 LIST(COUNT_ITEMS))

void setUp(void) {}
void tearDown(void) {}

void test_common_count(void) {
  TEST_ASSERT_EQUAL_INT(EXPECTED_COUNT, LIST_COUNT);
  TEST_ASSERT_NOT_EQUAL_INT(EXPECTED_COUNT - 1, LIST_COUNT);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_common_count);

  return UNITY_END();
}
