#include <unity.h>

#include "../src/service/service.h"
#include "../src/component_id.h"

void setUp(void) {}
void tearDown(void) {}

// TODO: extend equal tests with weird edge cases
void test_cmp_equals(void) {
	shdrt_Service s = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_Service s2 = { .id = shdrt_ComponentIdentifier_make("foo", "bar") };
	shdrt_Service s3 = { .id = shdrt_ComponentIdentifier_make("dead", "beef") };

	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s, &s2) == 0);
	TEST_ASSERT_FALSE(shdrt_Service_cmp(&s, &s3) == 0);

	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s2, &s) == 0);
	TEST_ASSERT_FALSE(shdrt_Service_cmp(&s2, &s3) == 0);

	TEST_ASSERT_FALSE(shdrt_Service_cmp(&s3, &s) == 0);
	TEST_ASSERT_FALSE(shdrt_Service_cmp(&s3, &s2) == 0);
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

void test_cmp_ordering(void) {
	shdrt_Service s11 = { .id = shdrt_ComponentIdentifier_make("aaa", "aaa") };
	shdrt_Service s12 = { .id = shdrt_ComponentIdentifier_make("aaa", "bbb") };

	shdrt_Service s21 = { .id = shdrt_ComponentIdentifier_make("bbb", "aaa") };
	shdrt_Service s22 = { .id = shdrt_ComponentIdentifier_make("bbb", "bbb") };

	shdrt_Service s31 = { .id = shdrt_ComponentIdentifier_make("casd", "undear") };
	shdrt_Service s32 = { .id = shdrt_ComponentIdentifier_make("casd", "zorrrr") };

	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s11, &s12) < 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s11, &s21) < 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s11, &s22) < 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s11, &s31) < 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s11, &s32) < 0);

	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s12, &s11) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s12, &s21) < 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s12, &s22) < 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s12, &s31) < 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s12, &s32) < 0);

	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s21, &s11) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s21, &s12) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s21, &s22) < 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s21, &s31) < 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s21, &s32) < 0);

	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s22, &s11) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s22, &s12) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s22, &s21) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s22, &s31) < 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s22, &s32) < 0);

	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s31, &s11) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s31, &s12) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s31, &s21) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s31, &s22) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s31, &s32) < 0);

	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s32, &s11) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s32, &s12) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s32, &s21) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s32, &s22) > 0);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(&s32, &s31) > 0);
}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_cmp_equals);
	RUN_TEST(test_equals);

	RUN_TEST(test_cmp_ordering);

	return UNITY_END();
}
