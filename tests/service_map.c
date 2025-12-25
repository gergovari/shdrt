#include <unity.h>

#include "../src/service/map.h"
#include "../src/service/start_id.h"

typedef struct shdrt_ServiceManager shdrt_ServiceManager;

static shdrt_Service* global_s;
static shdrt_Service* global_s2;

void setUp(void) {
	global_s = c_new(shdrt_Service, {
		.id = { .package = cstr_from("dead"), .name = cstr_from("beef") },
		.on_start_command = NULL,
		.on_create = NULL,
		.on_destroy = NULL,
		.on_bind = NULL }
	);
	global_s2 = c_new(shdrt_Service, {
		.id = { .package = cstr_from("foo"), .name = cstr_from("bar") },
		.on_start_command = NULL,
		.on_create = NULL,
		.on_destroy = NULL,
		.on_bind = NULL }
	);
}

void tearDown(void) {
	c_free(global_s, sizeof(shdrt_Service));
	c_free(global_s2, sizeof(shdrt_Service));
}

void dummy_func(shdrt_ServiceManager* man, shdrt_ServiceStartId id) {}

void test_add(void) {
	int dummy = 1;
	shdrt_ServiceMap map = {0};

	shdrt_ServiceContext* ctx = shdrt_ServiceMap_add(&map, *global_s, &dummy, dummy_func);
	
	TEST_ASSERT_NOT_NULL(ctx);
	TEST_ASSERT_EQUAL_PTR(ctx->user, &dummy);
	TEST_ASSERT_EQUAL_PTR(ctx->stop, dummy_func);

	const shdrt_ServiceMap_value* val = shdrt_ServiceMap_get(&map, *global_s);
	TEST_ASSERT_TRUE(val);
	TEST_ASSERT_EQUAL_PTR(ctx, val->second);
	TEST_ASSERT_TRUE(shdrt_Service_cmp(global_s, &val->first) == 0);
	TEST_ASSERT_FALSE(shdrt_Service_cmp(global_s2, &val->first) == 0);

	shdrt_ServiceMap_drop(&map);
}

void test_delete(void) {
	shdrt_ServiceMap map = c_make(shdrt_ServiceMap, {*global_s});
	
	const shdrt_ServiceMap_value* val = shdrt_ServiceMap_get(&map, *global_s);
	const shdrt_ServiceMap_value* val2 = shdrt_ServiceMap_get(&map, *global_s2);
	TEST_ASSERT_TRUE(val);
	TEST_ASSERT_FALSE(val2);

	bool res = shdrt_ServiceMap_delete(&map, *global_s);
	bool res2 = shdrt_ServiceMap_delete(&map, *global_s2);

	TEST_ASSERT_TRUE(res);
	TEST_ASSERT_FALSE(res2);

	val = shdrt_ServiceMap_get(&map, *global_s);
	val2 = shdrt_ServiceMap_get(&map, *global_s2);
	TEST_ASSERT_FALSE(val);
	TEST_ASSERT_FALSE(val2);

	shdrt_ServiceMap_drop(&map);
}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_add);
	RUN_TEST(test_delete);

	return UNITY_END();
}
