#include <unity.h>

#include "../src/intent.h"
#include "../src/component_id.h"

void setUp(void) {}
void tearDown(void) {}

/* TODO:
 * order on id
 * order on action
 * order on if it has id
 * */
void test_cmp(void) {
	shdrt_Intent = {
		.id = shdrt_
	}
}

void test_equals(void) {

}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_cmp);
	RUN_TEST(test_equals);

	return UNITY_END();
}
