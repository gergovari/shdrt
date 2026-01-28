#include <sys/types.h>
#include <unity.h>

#include "../src/service/manager.h"
#include "stc/common.h"

void
setUp(void) {}

void
tearDown(void) {}

static bool created = false;
static bool destroyed = false;
static bool started = false;

typedef struct test_ctx {
    bool created;
    bool destroyed;
    bool started;
} test_ctx_t;

bool
on_create(shdrt_ServiceContext* ctx) {
    test_ctx_t* user = c_new(test_ctx_t, {.created = true, .destroyed = false, .started = false});

    ctx->user = user;
    created = true;

    TEST_ASSERT_TRUE(((test_ctx_t*)ctx->user)->created);
    TEST_ASSERT_FALSE(((test_ctx_t*)ctx->user)->destroyed);
    TEST_ASSERT_FALSE(((test_ctx_t*)ctx->user)->started);

    return user != NULL;
}

void
on_destroy(shdrt_ServiceContext* ctx) {
    destroyed = true;
    ((test_ctx_t*)ctx->user)->destroyed = true;

    TEST_ASSERT_TRUE(((test_ctx_t*)ctx->user)->created);
    TEST_ASSERT_TRUE(((test_ctx_t*)ctx->user)->destroyed);
    TEST_ASSERT_TRUE(((test_ctx_t*)ctx->user)->started);

    c_free(ctx->user, sizeof(test_ctx_t));
}

shdrt_ServiceContinuationMode
on_start_command(shdrt_ServiceContext* ctx, shdrt_Intent intent, shdrt_ServiceStartFlags flags,
                 shdrt_ServiceStartId id) {
    started = true;
    ((test_ctx_t*)ctx->user)->started = true;

    TEST_ASSERT_TRUE(((test_ctx_t*)ctx->user)->created);
    TEST_ASSERT_FALSE(((test_ctx_t*)ctx->user)->destroyed);
    TEST_ASSERT_TRUE(((test_ctx_t*)ctx->user)->started);

    return shdrt_SERVICE_START_NOT_STICKY;
}

typedef struct test_ctx2 {
    shdrt_ServiceStartId last;
    u_int8_t count;
} test_ctx2_t;

bool
on_create2(shdrt_ServiceContext* ctx) {
    test_ctx2_t* user = c_new(test_ctx2_t, {.count = 0});

    ctx->user = user;
    return user != NULL;
}

void
on_destroy2(shdrt_ServiceContext* ctx) {
    c_free(ctx->user, sizeof(test_ctx2_t));
}

static bool test_ran = false;

shdrt_ServiceContinuationMode
on_start_command2(shdrt_ServiceContext* ctx, shdrt_Intent intent, shdrt_ServiceStartFlags flags,
                  shdrt_ServiceStartId id) {
    test_ctx2_t* user = ctx->user;

    user->count++;
    if (user->count > 2) {
        TEST_ASSERT_FALSE(ctx->stop(ctx->man, user->last));
        TEST_ASSERT_TRUE(ctx->stop(ctx->man, id));
        test_ran = true;
    } else {
        user->last = id;
    }

    return shdrt_SERVICE_START_NOT_STICKY;
}

void
test_start_stop() {
    c_with(shdrt_ServiceManager man = shdrt_ServiceManager_make(), shdrt_ServiceManager_drop(&man)) {
        shdrt_Service s = {.on_create = on_create, .on_destroy = on_destroy, .on_start_command = on_start_command};
        shdrt_Intent intent = {};

        shdrt_ServiceManager_start(&man, s, intent);
        TEST_ASSERT_TRUE(created);
        TEST_ASSERT_TRUE(started);
        TEST_ASSERT_FALSE(destroyed);

        shdrt_ServiceManager_stop(&man, s);
        TEST_ASSERT_TRUE(destroyed);
    }
}

void
test_stop_self() {
    c_with(shdrt_ServiceManager man = shdrt_ServiceManager_make(), shdrt_ServiceManager_drop(&man)) {
        shdrt_Service s = {.on_create = on_create2, .on_destroy = on_destroy2, .on_start_command = on_start_command2};
        shdrt_Intent intent = {};

        shdrt_ServiceManager_start(&man, s, intent);
        shdrt_ServiceManager_start(&man, s, intent);
        shdrt_ServiceManager_start(&man, s, intent);
    }
    TEST_ASSERT_TRUE(test_ran);
}

int
main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_start_stop);
    RUN_TEST(test_stop_self);

    return UNITY_END();
}
