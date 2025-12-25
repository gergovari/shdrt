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
}

void test_stop(void) {

}

void test_get_service(void) {}

void test_forget(void) {}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_start);
	RUN_TEST(test_stop);
	RUN_TEST(test_get_service);
	RUN_TEST(test_forget);

	return UNITY_END();
}
