#include <unity.h>

#include <stc/common.h>
#include <stc/cstr.h>

#include "../src/component_id.h"

static const char* package = "merry";
static const char* name = "christmas";

static shdrt_ComponentIdentifier* global;

void setUp(void) {
	global = c_new(shdrt_ComponentIdentifier, { .package = cstr_from(package), .name = cstr_from(name) });
}

void tearDown(void) {
	c_free(global, sizeof(shdrt_ComponentIdentifier));
}


void test_make(void) {
	shdrt_ComponentIdentifier id = shdrt_ComponentIdentifier_make(package, name);

	TEST_ASSERT_EQUAL_STRING(package, cstr_str(&id.package));
	TEST_ASSERT_EQUAL_STRING(name, cstr_str(&id.name));
}

void test_clone(void) {
	shdrt_ComponentIdentifier id2 = shdrt_ComponentIdentifier_clone(*global);
	
	TEST_ASSERT_EQUAL_STRING(cstr_str(&global->package), cstr_str(&id2.package));
	TEST_ASSERT_EQUAL_STRING(cstr_str(&global->name), cstr_str(&id2.name));
}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_make);
	RUN_TEST(test_clone);

	return UNITY_END();
}
