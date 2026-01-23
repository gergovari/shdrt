#include <unity.h>

#include "../src/component_id.h"

#include "../src/service/binder.h"
#include "../src/service/binder_map.h"

void setUp(void) {}
void tearDown(void) {}

void test_add2() {
  shdrt_ServiceBinderMap map = {0};

  shdrt_Service s = {.id = shdrt_ComponentIdentifier_make("shd", "test")};

  shdrt_Intent intent = {.id = shdrt_ComponentIdentifier_make("shd", "intent"),
                         .explicitId = true};
  shdrt_Intent intent2 = {.id =
                              shdrt_ComponentIdentifier_make("shd", "intent2"),
                          .explicitId = true};

  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_add(&map, s, intent, NULL));
  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_add(&map, s, intent2, NULL));

  const shdrt_ServiceBinderMap_value *res = shdrt_ServiceBinderMap_get(&map, s);

  TEST_ASSERT_FALSE(res == NULL);

  TEST_ASSERT_TRUE(shdrt_ServiceIntentBinderMap_contains(&res->second, intent));
  TEST_ASSERT_TRUE(
      shdrt_ServiceIntentBinderMap_contains(&res->second, intent2));
}
void test_delete2() {
  shdrt_ServiceBinderMap map = {0};

  shdrt_Service s = {.id = shdrt_ComponentIdentifier_make("shd", "test")};

  shdrt_Intent intent = {.id = shdrt_ComponentIdentifier_make("shd", "intent"),
                         .explicitId = true};
  shdrt_Intent intent2 = {.id =
                              shdrt_ComponentIdentifier_make("shd", "intent2"),
                          .explicitId = true};

  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_add(&map, s, intent, NULL));
  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_add(&map, s, intent2, NULL));

  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_delete(&map, s));

  const shdrt_ServiceBinderMap_value *res = shdrt_ServiceBinderMap_get(&map, s);
  TEST_ASSERT_TRUE(res == NULL);
}

void test_add() {
  shdrt_ServiceBinderMap map = {0};

  shdrt_Service s = {.id = shdrt_ComponentIdentifier_make("shd", "test")};

  shdrt_Intent intent = {0};

  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_add(&map, s, intent, NULL));

  const shdrt_ServiceBinderMap_value *res = shdrt_ServiceBinderMap_get(&map, s);

  TEST_ASSERT_FALSE(res == NULL);

  TEST_ASSERT_TRUE(shdrt_ServiceIntentBinderMap_contains(&res->second, intent));
}
void test_delete() {
  shdrt_ServiceBinderMap map = {0};

  shdrt_Service s = {.id = shdrt_ComponentIdentifier_make("shd", "test")};

  shdrt_Intent intent = {0};

  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_add(&map, s, intent, NULL));
  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_delete(&map, s));

  const shdrt_ServiceBinderMap_value *res = shdrt_ServiceBinderMap_get(&map, s);
  TEST_ASSERT_TRUE(res == NULL);
}

void test_add_multiple() {
  shdrt_ServiceBinderMap map = {0};

  shdrt_Service s = {.id = shdrt_ComponentIdentifier_make("shd", "test")};
  shdrt_Service s2 = {.id = shdrt_ComponentIdentifier_make("shd", "test2")};

  shdrt_Intent intent = {0};

  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_add(&map, s, intent, NULL));
  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_add(&map, s2, intent, NULL));

  const shdrt_ServiceBinderMap_value *res = shdrt_ServiceBinderMap_get(&map, s);
  const shdrt_ServiceBinderMap_value *res2 =
      shdrt_ServiceBinderMap_get(&map, s);

  TEST_ASSERT_FALSE(res == NULL);
  TEST_ASSERT_FALSE(res2 == NULL);

  TEST_ASSERT_TRUE(shdrt_ServiceIntentBinderMap_contains(&res->second, intent));
  TEST_ASSERT_TRUE(
      shdrt_ServiceIntentBinderMap_contains(&res2->second, intent));
}
void test_delete_multiple() {
  shdrt_ServiceBinderMap map = {0};

  shdrt_Service s = {.id = shdrt_ComponentIdentifier_make("shd", "test")};
  shdrt_Service s2 = {.id = shdrt_ComponentIdentifier_make("shd", "test2")};

  shdrt_Intent intent = {0};

  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_add(&map, s, intent, NULL));
  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_add(&map, s2, intent, NULL));
  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_delete(&map, s));
  TEST_ASSERT_TRUE(shdrt_ServiceBinderMap_delete(&map, s2));

  const shdrt_ServiceBinderMap_value *res = shdrt_ServiceBinderMap_get(&map, s);
  const shdrt_ServiceBinderMap_value *res2 =
      shdrt_ServiceBinderMap_get(&map, s);

  TEST_ASSERT_TRUE(res == NULL);
  TEST_ASSERT_TRUE(res2 == NULL);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_add);
  RUN_TEST(test_delete);

  RUN_TEST(test_add_multiple);
  RUN_TEST(test_delete_multiple);

  RUN_TEST(test_add2);
  RUN_TEST(test_delete2);

  return UNITY_END();
}
