#include <unity.h>

#include "../src/intent/intent.h"
#include "../src/component_id.h"

void setUp(void) {}
void tearDown(void) {}

/* TODO:
 * order on id
 * order on action
 * order on if it has id
 * */
void test_cmp(void) {
	shdrt_Intent one = {
		.id = shdrt_ComponentIdentifier_make("a", "a"),
		.action = shdrt_IntentAction_make(SHDRT_INTENT_ACTION_MAIN)
	};
}

void test_equals(void) {

}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_cmp);
	RUN_TEST(test_equals);

	return UNITY_END();
}
