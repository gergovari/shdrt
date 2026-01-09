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

void test_start_multiple(void) {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_Service s2 = { .id = shdrt_ComponentIdentifier_make("dead", "beef") };

	shdrt_ServiceStartIdMap map = {0};

	shdrt_ServiceStartId id;
	shdrt_ServiceStartId id2;

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s, &id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s2, &id2));

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_contains(&map, id2));

	shdrt_ServiceStartIdMap_drop(&map);
}

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

void test_stop_multiple(void) {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_Service s2 = { .id = shdrt_ComponentIdentifier_make("dead", "beef") };

	shdrt_ServiceStartIdMap map = {0};

	shdrt_ServiceStartId id;
	shdrt_ServiceStartId id2;

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s, &id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s2, &id2));

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_stop(&map, id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_stop(&map, id2));

	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_stop(&map, id));

	shdrt_ServiceStartIdMap_drop(&map);
}

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

void test_forget_multiple(void) {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_Service s2 = { .id = shdrt_ComponentIdentifier_make("dead", "beef") };

	shdrt_ServiceStartIdMap map = {0};

	shdrt_ServiceStartId id;
	shdrt_ServiceStartId id2;

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s, &id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s2, &id2));
	
	shdrt_ServiceStartIdMap_forget(&map, s);
	shdrt_ServiceStartIdMap_forget(&map, s2);

	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id2));

	shdrt_ServiceStartIdMap_drop(&map);
}

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
	TEST_ASSERT_TRUE(shdrt_Service_equals(&s, &s2));

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_stop(&map, id));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_get_service(&map, id, &s2));

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s, &id));
	shdrt_ServiceStartIdMap_forget(&map, s);
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_contains(&map, id));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_get_service(&map, id, &s2));
}

void test_get_service_multiple(void) {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_Service s2 = { .id = shdrt_ComponentIdentifier_make("dead", "beef") };

	shdrt_Service sout = { 0 };
	shdrt_Service s2out = { 0 };

	shdrt_ServiceStartIdMap map = {0};

	shdrt_ServiceStartId id;
	shdrt_ServiceStartId id2;
	
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s, &id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_start(&map, s2, &id2));

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_get_service(&map, id, &sout));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_get_service(&map, id2, &s2out));

	TEST_ASSERT_TRUE(shdrt_Service_equals(&s, &sout));
	TEST_ASSERT_TRUE(shdrt_Service_equals(&s2, &s2out));

	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_stop(&map, id));
	TEST_ASSERT_TRUE(shdrt_ServiceStartIdMap_stop(&map, id2));

	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_get_service(&map, id, &sout));
	TEST_ASSERT_FALSE(shdrt_ServiceStartIdMap_get_service(&map, id, &s2out));
}

// TODO: test for start_id stop behaviour

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_start);
	RUN_TEST(test_start_multiple);

	RUN_TEST(test_stop);
	RUN_TEST(test_stop_multiple);

	RUN_TEST(test_forget);
	RUN_TEST(test_forget_multiple);

	RUN_TEST(test_get_service);
	RUN_TEST(test_get_service_multiple);

	return UNITY_END();
}
