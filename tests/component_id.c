#include <unity.h>

#include <stc/cstr.h>

#include "../src/component_id.h"

void setUp(void) {}
void tearDown(void) {}

static const char* package = "merry";
static const char* name = "christmas";

void test_make(void) {
	shdrt_ComponentIdentifier id = shdrt_ComponentIdentifier_make(package, name);

	TEST_ASSERT_EQUAL_STRING(package, cstr_str(&id.package));
	TEST_ASSERT_EQUAL_STRING(name, cstr_str(&id.name));
}

void test_clone(void) {
	shdrt_ComponentIdentifier id = shdrt_ComponentIdentifier_make(package, name);
	shdrt_ComponentIdentifier id2 = shdrt_ComponentIdentifier_clone(id);
	
	TEST_ASSERT_EQUAL_STRING(cstr_str(&id.package), cstr_str(&id2.package));
	TEST_ASSERT_EQUAL_STRING(cstr_str(&id.name), cstr_str(&id2.name));
}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_make);
	RUN_TEST(test_clone);

	return UNITY_END();
}
