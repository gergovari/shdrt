#include <unity.h>

#include <string.h>

#include <stc/common.h>
#include <stc/cstr.h>

#include "../src/component_id.h"

static const char* package = "merry";
static const char* name = "christmas";

static const char* package2 = "happy";
static const char* name2 = "holidays";

static shdrt_ComponentIdentifier* global;
static shdrt_ComponentIdentifier* global2;

void setUp(void) {
	global = c_new(shdrt_ComponentIdentifier, { .package = cstr_from(package), .name = cstr_from(name) });
	global2 = c_new(shdrt_ComponentIdentifier, { .package = cstr_from(package2), .name = cstr_from(name2) });
}

void tearDown(void) {
	shdrt_ComponentIdentifier_drop(global);
	shdrt_ComponentIdentifier_drop(global2);

	c_free(global, sizeof(shdrt_ComponentIdentifier));
	c_free(global2, sizeof(shdrt_ComponentIdentifier));
}


void test_make(void) {
	shdrt_ComponentIdentifier id = shdrt_ComponentIdentifier_make(package, name);

	TEST_ASSERT_EQUAL_STRING(package, cstr_str(&id.package));
	TEST_ASSERT_EQUAL_STRING(name, cstr_str(&id.name));

	TEST_ASSERT_TRUE(strcmp(package2, cstr_str(&id.package)) != 0);
	TEST_ASSERT_TRUE(strcmp(name2, cstr_str(&id.name)) != 0);

	shdrt_ComponentIdentifier_drop(&id);
}

void test_clone(void) {
	shdrt_ComponentIdentifier id2 = shdrt_ComponentIdentifier_clone(*global);
	
	TEST_ASSERT_EQUAL_STRING(cstr_str(&global->package), cstr_str(&id2.package));
	TEST_ASSERT_EQUAL_STRING(cstr_str(&global->name), cstr_str(&id2.name));

	TEST_ASSERT_TRUE(strcmp(cstr_str(&global2->package), cstr_str(&id2.package)) != 0);
	TEST_ASSERT_TRUE(strcmp(cstr_str(&global2->name), cstr_str(&id2.name)) != 0);

	shdrt_ComponentIdentifier_drop(&id2);
}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_make);
	RUN_TEST(test_clone);

	return UNITY_END();
}
