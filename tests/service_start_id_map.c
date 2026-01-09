#include <unity.h>

#include "../src/service/start_id_map.h"

void setUp(void) {}
void tearDown(void) {}

void test_start(void) {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_ServiceStartIdMap map = {0};
	shdrt_ServiceStartId id;

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s, &id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id+1));

	shdrt_ServiceStartIdMap_drop(&map);
}

// TODO: test for multiple start

void test_stop(void) {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_ServiceStartIdMap map = {0};
	shdrt_ServiceStartId id = 0;

	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_stop(&map, id));
	
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s, &id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_stop(&map, id));

	shdrt_ServiceStartIdMap_drop(&map);	
}

// TODO: test for multiple stop

void test_forget(void) {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_ServiceStartIdMap map = {0};
	shdrt_ServiceStartId id;

	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id));
	shdrt_ServiceStartIdMap_forget(&map, s);
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id));

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s, &id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_contains(&map, id));
	shdrt_ServiceStartIdMap_forget(&map, s);
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id));
}

// TODO: test for multiple forget

void test_get_service(void) {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_ServiceStartIdMap map = {0};
	shdrt_ServiceStartId id;
	shdrt_Service s2 = { 0 };
	
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_get_service(&map, id, &s2));

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s, &id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_get_service(&map, id, &s2));
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s, &s2) == 0);

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_stop(&map, id));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_get_service(&map, id, &s2));

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s, &id));
	shdrt_ServiceStartIdMap_forget(&map, s);
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_get_service(&map, id, &s2));
}

// TODO: test for multiple get_service

// TODO: test for start_id stop behaviour

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_start);
	RUN_TEST(test_stop);
	RUN_TEST(test_forget);
	RUN_TEST(test_get_service);

	return UNITY_END();
}
