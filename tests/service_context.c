#include <unity.h>

#include "../src/service/context.h"

void setUp(void) {}
void tearDown(void) {}

void test_add(void) {
	
}

void test_delete(void) {}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_add);
	RUN_TEST(test_delete);

	return UNITY_END();
}
