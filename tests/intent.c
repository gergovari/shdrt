#include <unity.h>

#include "../src/intent/intent.h"
#include "../src/component_id.h"

#include <stc/cstr.h>

void setUp(void) {}
void tearDown(void) {}

void test_cmp(void) {
	shdrt_Intent a1 = {
		.id = shdrt_ComponentIdentifier_make("a", "a"),
		.explicitId = true
	};
	shdrt_Intent b1 = {
		.id = shdrt_ComponentIdentifier_make("b", "b"),
		.explicitId = true
	};

	shdrt_Intent a2 = {
		.action = shdrt_IntentAction_make(SHDRT_INTENT_ACTION_MAIN),
		.explicitAction = true
	};
	shdrt_Intent b2 = {
		.action = shdrt_IntentAction_make(SHDRT_INTENT_ACTION_VIEW),
		.explicitAction = true
	};

	TEST_ASSERT_TRUE(shdrt_Intent_cmp(&a1, &b1) < 0);
	TEST_ASSERT_TRUE(shdrt_Intent_cmp(&a2, &b2) < 0);
	TEST_ASSERT_TRUE(shdrt_Intent_cmp(&a1, &a2) < 0);
}

void test_equals(void) {
	shdrt_Intent a1 = {
		.id = shdrt_ComponentIdentifier_make("a", "a"),
		.explicitId = true
	};
	shdrt_Intent b1 = {
		.id = shdrt_ComponentIdentifier_make("b", "b"),
		.explicitId = true
	};

	shdrt_Intent a2 = {
		.id = shdrt_ComponentIdentifier_make("a", "a"),
		.explicitId = true,

		.action = shdrt_IntentAction_make(SHDRT_INTENT_ACTION_MAIN),
		.explicitAction = true,

		.data = cstr_lit("data"),
		.explicitData = true,

		.type = cstr_lit("type"),
		.explicitType = true,

		.flags = SHDRT_INTENT_FLAG_ACTIVITY_NEW_TASK || SHDRT_INTENT_FLAG_ACTIVITY_SINGLE_TOP,
		.extra = NULL
	};
	shdrt_Intent b2 = {
		.id = shdrt_ComponentIdentifier_make("b", "b"),
		.explicitId = true,

		.action = shdrt_IntentAction_make(SHDRT_INTENT_ACTION_MAIN),
		.explicitAction = true,

		.data = cstr_lit("data"),
		.explicitData = true,

		.type = cstr_lit("type"),
		.explicitType = true,

		.flags = SHDRT_INTENT_FLAG_ACTIVITY_NEW_TASK || SHDRT_INTENT_FLAG_ACTIVITY_SINGLE_TOP
	};

	shdrt_Intent a2x = {
		.id = shdrt_ComponentIdentifier_make("a", "a"),
		.explicitId = true,

		.action = shdrt_IntentAction_make(SHDRT_INTENT_ACTION_MAIN),
		.explicitAction = true,

		.data = cstr_lit("data"),
		.explicitData = true,

		.type = cstr_lit("type"),
		.explicitType = true,

		.flags = SHDRT_INTENT_FLAG_ACTIVITY_NEW_TASK || SHDRT_INTENT_FLAG_ACTIVITY_SINGLE_TOP,
		.extra = (void*)1
	};

	TEST_ASSERT_TRUE(shdrt_Intent_equals(&a1, &a1));
	TEST_ASSERT_FALSE(shdrt_Intent_equals(&a1, &b1));

	TEST_ASSERT_TRUE(shdrt_Intent_equals(&a2, &a2));
	TEST_ASSERT_FALSE(shdrt_Intent_equals(&a2, &b2));

	TEST_ASSERT_TRUE(shdrt_Intent_equals(&a2, &a2x));
}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_cmp);
	RUN_TEST(test_equals);

	return UNITY_END();
}
