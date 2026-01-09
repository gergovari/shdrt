#include <unity.h>

#include "../src/service/service.h"
#include "../src/component_id.h"

void setUp(void) {}
void tearDown(void) {}

void test_cmp(void) {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_Service s2 = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_Service s3 = { .id = shdrt_ComponentIdentifier_make("dead", "beef") };

	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s, &s2) == 0);
	TEST_ASSERT_FALSE(shdrt_Service_cmp(&s, &s3) == 0);

	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s2, &s) == 0);
	TEST_ASSERT_FALSE(shdrt_Service_cmp(&s2, &s3) == 0);

	TEST_ASSERT_FALSE(shdrt_Service_cmp(&s3, &s) == 0);
	TEST_ASSERT_FALSE(shdrt_Service_cmp(&s3, &s2) == 0);

	// TODO: test for ordering
}

void test_equals() {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_Service s2 = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_Service s3 = { .id = shdrt_ComponentIdentifier_make("dead", "beef") };

	TEST_ASSERT_TRUE(shdrt_Service_equals(&s, &s2));
	TEST_ASSERT_FALSE(shdrt_Service_equals(&s, &s3));

	TEST_ASSERT_TRUE(shdrt_Service_equals(&s2, &s));
	TEST_ASSERT_FALSE(shdrt_Service_equals(&s2, &s3));

	TEST_ASSERT_FALSE(shdrt_Service_equals(&s3, &s));
	TEST_ASSERT_FALSE(shdrt_Service_equals(&s3, &s2));
}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_cmp);
	RUN_TEST(test_equals);

	return UNITY_END();
}
