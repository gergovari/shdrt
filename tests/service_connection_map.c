#include <unity.h>

#include "../src/component_id.h"

#include "../src/service/connection.h"
#include "../src/service/connection_map.h"

void setUp(void) {}
void tearDown(void) {}

void test_add() {
  shdrt_ServiceConnectionMap map = {0};

  shdrt_Service s = {.id = shdrt_ComponentIdentifier_make("shd", "test")};

  shdrt_ServiceConnection conn = {0};

  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_add(&map, s, &conn));

  const shdrt_ServiceConnectionMap_value *res =
      shdrt_ServiceConnectionMap_get(&map, s);

  TEST_ASSERT_FALSE(res == NULL);

  TEST_ASSERT_TRUE(shdrt_ServiceConnectionSet_contains(&res->second, &conn));
}

void test_add_multiple() {
  shdrt_ServiceConnectionMap map = {0};

  shdrt_Service s = {.id = shdrt_ComponentIdentifier_make("shd", "test")};
  shdrt_Service s2 = {.id = shdrt_ComponentIdentifier_make("shd", "test2")};

  shdrt_ServiceConnection conn = {0};
  shdrt_ServiceConnection conn2 = {0};

  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_add(&map, s, &conn));
  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_add(&map, s2, &conn2));

  const shdrt_ServiceConnectionMap_value *res =
      shdrt_ServiceConnectionMap_get(&map, s);
  const shdrt_ServiceConnectionMap_value *res2 =
      shdrt_ServiceConnectionMap_get(&map, s2);

  TEST_ASSERT_FALSE(res == NULL);
  TEST_ASSERT_FALSE(res2 == NULL);

  TEST_ASSERT_TRUE(shdrt_ServiceConnectionSet_contains(&res->second, &conn));
  TEST_ASSERT_TRUE(shdrt_ServiceConnectionSet_contains(&res2->second, &conn2));
}

void test_delete() {
  shdrt_ServiceConnectionMap map = {0};

  shdrt_Service s = {.id = shdrt_ComponentIdentifier_make("shd", "test")};
  shdrt_ServiceConnection conn = {0};

  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_add(&map, s, &conn));

  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_delete(&map, &conn));

  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_get(&map, s) == NULL);
}

void test_delete_multiple() {
  shdrt_ServiceConnectionMap map = {0};

  shdrt_Service s = {.id = shdrt_ComponentIdentifier_make("shd", "test")};
  shdrt_Service s2 = {.id = shdrt_ComponentIdentifier_make("shd", "test2")};

  shdrt_ServiceConnection conn = {0};
  shdrt_ServiceConnection conn2 = {0};

  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_add(&map, s, &conn));
  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_add(&map, s, &conn2));

  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_delete(&map, &conn));
  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_delete(&map, &conn2));

  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_get(&map, s) == NULL);
  TEST_ASSERT_TRUE(shdrt_ServiceConnectionMap_get(&map, s2) == NULL);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_add);
  RUN_TEST(test_add_multiple);

  RUN_TEST(test_delete);
  RUN_TEST(test_delete_multiple);

  return UNITY_END();
}
