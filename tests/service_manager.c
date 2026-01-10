#include <unity.h>

#include <stc/common.h>

#include "../src/service/service.h"
#include "../src/service/continuation_mode.h"
#include "../src/service/manager.h"

static bool ranStart = false;
static bool ranCreate = false;
static bool ranDestroy = false;

typedef struct {
	bool ranStart;
	bool ranCreate;
	bool ranDestroy;
} test_ServiceManagerTest_ServiceContext;
void test_ServiceManagerTest_ServiceContext_drop() {}

void setUp(void) {
	ranStart = false;
	ranCreate = false;
	ranDestroy = false;
}

void tearDown(void) {}

bool on_create(shdrt_ServiceContext* raw) {
	test_ServiceManagerTest_ServiceContext* ctx = c_new(test_ServiceManagerTest_ServiceContext, { .ranCreate = true });

	raw->user = ctx;
	ranCreate = true;
	
	return true;
}

shdrt_ServiceContinuationMode on_start_command(shdrt_ServiceContext* raw, shdrt_Intent intent, shdrt_ServiceStartFlags flags, shdrt_ServiceStartId id) {
	test_ServiceManagerTest_ServiceContext* ctx = raw->user;

	TEST_ASSERT_TRUE(ctx->ranCreate);

	ranStart = true;
	ctx->ranStart = true;

	return shdrt_SERVICE_START_NOT_STICKY;
}

void on_destroy(shdrt_ServiceContext* raw) {
	test_ServiceManagerTest_ServiceContext* ctx = raw->user;

	TEST_ASSERT_TRUE(ctx->ranCreate);
	TEST_ASSERT_TRUE(ctx->ranStart);

	ranDestroy = true;
	ctx->ranDestroy = true;

	c_delete_n(test_ServiceManagerTest_ServiceContext, ctx, 1);
}

void test_start(void) {
	shdrt_Service s = {
		.id = shdrt_ComponentIdentifier_make("shd.comm", "imaginary"),
		.on_start_command = on_start_command,
		.on_create = on_create,
		.on_destroy = NULL,
		.on_bind = NULL
	};
	shdrt_Intent intent = { 0 };

	c_with (shdrt_ServiceManager man = shdrt_ServiceManager_make(), shdrt_ServiceManager_drop(&man)) {
		TEST_ASSERT_FALSE(ranStart);
		TEST_ASSERT_FALSE(ranCreate);

		TEST_ASSERT_TRUE(shdrt_ServiceManager_start(&man, s, intent));
		TEST_ASSERT_TRUE(ranStart);
		TEST_ASSERT_TRUE(ranCreate);
	}

}

void test_stop(void) {
	shdrt_Service s = {
		.id = shdrt_ComponentIdentifier_make("shd.comm", "imaginary"),
		.on_start_command = on_start_command,
		.on_create = on_create,
		.on_destroy = on_destroy,
		.on_bind = NULL
	};
	shdrt_Intent intent = { 0 };

	c_with (shdrt_ServiceManager man = shdrt_ServiceManager_make(), shdrt_ServiceManager_drop(&man)) {
		TEST_ASSERT_FALSE(ranDestroy);

		TEST_ASSERT_TRUE(shdrt_ServiceManager_start(&man, s, intent));
		TEST_ASSERT_FALSE(ranDestroy);

		shdrt_ServiceManager_stop(&man, s);
		TEST_ASSERT_TRUE(ranDestroy);
	}
}

typedef struct {
	int count;
} test_ServiceManagerTest_ServiceSelfContext;
void test_ServiceManagerTest_ServiceSelfContext_drop() {}

bool on_create_self(shdrt_ServiceContext* raw) {
	test_ServiceManagerTest_ServiceSelfContext* ctx = c_new(test_ServiceManagerTest_ServiceSelfContext, { .count = 0 });

	raw->user = ctx;

	return true;
}

shdrt_ServiceContinuationMode on_start_command_self(shdrt_ServiceContext* raw, shdrt_Intent intent, shdrt_ServiceStartFlags flags, shdrt_ServiceStartId id) {
	test_ServiceManagerTest_ServiceSelfContext* ctx = raw->user;
	
	ctx->count++;
	
	printf("%d\n", ctx->count);
	if (ctx->count > 2) raw->stop(raw->man, id);
	return shdrt_SERVICE_START_NOT_STICKY;
}

void on_destroy_self(shdrt_ServiceContext* raw) {
	test_ServiceManagerTest_ServiceSelfContext* ctx = raw->user;
	
	ranDestroy = true;

	c_delete_n(test_ServiceManagerTest_ServiceSelfContext, ctx, 1);
}

void test_stop_self(void) {
	shdrt_Service s = {
		.id = shdrt_ComponentIdentifier_make("shd.comm", "imaginary"),
		.on_start_command = on_start_command_self,
		.on_create = on_create_self,
		.on_destroy = on_destroy_self,
		.on_bind = NULL
	};
	shdrt_Intent intent = { 0 };

	c_with (shdrt_ServiceManager man = shdrt_ServiceManager_make(), shdrt_ServiceManager_drop(&man)) {
		TEST_ASSERT_FALSE(ranDestroy);

		TEST_ASSERT_TRUE(shdrt_ServiceManager_start(&man, s, intent));
		TEST_ASSERT_FALSE(ranDestroy);

		TEST_ASSERT_TRUE(shdrt_ServiceManager_start(&man, s, intent));
		TEST_ASSERT_FALSE(ranDestroy);

		TEST_ASSERT_TRUE(shdrt_ServiceManager_start(&man, s, intent));
		TEST_ASSERT_TRUE(ranDestroy);
	}
}

// TODO: multiples
int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_start);
	//RUN_TEST(test_start_multiple);

	RUN_TEST(test_stop);
	//RUN_TEST(test_stop_multiple);

	RUN_TEST(test_stop_self);
	//RUN_TEST(test_stop_self_multiple);

	return UNITY_END();
}
