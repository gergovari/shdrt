#include <unity.h>

#include "../src/service/context_map.h"
#include "../src/service/start_id.h"

typedef struct shdrt_ServiceManager shdrt_ServiceManager;

static shdrt_Service* global_s;
static shdrt_Service* global_s2;

bool
dummy_func(shdrt_ServiceManager* man, shdrt_ServiceStartId id) {
    return true;
}

bool
dummy_on_create(shdrt_ServiceContext* ctx) {
    return true;
}

void
dummy_on_destroy(shdrt_ServiceContext* ctx) {}

void
setUp(void) {
    global_s = c_new(shdrt_Service, {.id = {.package = cstr_from("dead"), .name = cstr_from("beef")},
                                     .on_start_command = NULL,
                                     .on_create = dummy_on_create,
                                     .on_destroy = dummy_on_destroy,
                                     .on_bind = NULL});
    global_s2 = c_new(shdrt_Service, {.id = {.package = cstr_from("foo"), .name = cstr_from("bar")},
                                      .on_start_command = NULL,
                                      .on_create = dummy_on_create,
                                      .on_destroy = dummy_on_destroy,
                                      .on_bind = NULL});
}

void
tearDown(void) {
    c_free(global_s, sizeof(shdrt_Service));
    c_free(global_s2, sizeof(shdrt_Service));
}

void
test_add(void) {
    shdrt_ServiceContextMap map = {0};

    shdrt_ServiceContext* ctx = shdrt_ServiceContextMap_create(&map, *global_s, NULL, dummy_func);

    TEST_ASSERT_NOT_NULL(ctx);
    TEST_ASSERT_EQUAL_PTR(ctx->stop, dummy_func);

    const shdrt_ServiceContextMap_value* val = shdrt_ServiceContextMap_get(&map, *global_s);
    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_EQUAL_PTR(ctx, val->second);
    TEST_ASSERT_TRUE(shdrt_Service_cmp(global_s, &val->first) == 0);
    TEST_ASSERT_FALSE(shdrt_Service_cmp(global_s2, &val->first) == 0);

    shdrt_ServiceContextMap_drop(&map);
}

void
test_add_multiple(void) {
    shdrt_ServiceContextMap map = {0};
    shdrt_Service calc = {.id = {.package = cstr_from("shd"), .name = cstr_from("calculator")},
                          .on_start_command = NULL,
                          .on_create = dummy_on_create,
                          .on_destroy = dummy_on_destroy,
                          .on_bind = NULL};
    shdrt_Service comm = {.id = {.package = cstr_from("shd"), .name = cstr_from("communication")},
                          .on_start_command = NULL,
                          .on_create = dummy_on_create,
                          .on_destroy = dummy_on_destroy,
                          .on_bind = NULL};
    shdrt_Service sett = {.id = {.package = cstr_from("shd"), .name = cstr_from("settings")},
                          .on_start_command = NULL,
                          .on_create = dummy_on_create,
                          .on_destroy = dummy_on_destroy,
                          .on_bind = NULL};
    shdrt_Service thirdp = {.id = {.package = cstr_from("acme"), .name = cstr_from("banking")},
                            .on_start_command = NULL,
                            .on_create = dummy_on_create,
                            .on_destroy = dummy_on_destroy,
                            .on_bind = NULL};

    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_create(&map, calc, NULL, NULL));
    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_create(&map, comm, NULL, NULL));
    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_create(&map, sett, NULL, NULL));
    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_create(&map, thirdp, NULL, NULL));

    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_get(&map, calc));
    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_get(&map, comm));
    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_get(&map, sett));
    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_get(&map, thirdp));
}

void
test_delete(void) {
    shdrt_ServiceContextMap map = c_make(shdrt_ServiceContextMap, {*global_s});

    const shdrt_ServiceContextMap_value* val = shdrt_ServiceContextMap_get(&map, *global_s);
    const shdrt_ServiceContextMap_value* val2 = shdrt_ServiceContextMap_get(&map, *global_s2);
    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_FALSE(val2);

    bool res = shdrt_ServiceContextMap_destroy(&map, *global_s);
    bool res2 = shdrt_ServiceContextMap_destroy(&map, *global_s2);

    TEST_ASSERT_TRUE(res);
    TEST_ASSERT_FALSE(res2);

    val = shdrt_ServiceContextMap_get(&map, *global_s);
    val2 = shdrt_ServiceContextMap_get(&map, *global_s2);
    TEST_ASSERT_FALSE(val);
    TEST_ASSERT_FALSE(val2);

    shdrt_ServiceContextMap_drop(&map);
}

void
test_delete_multiple(void) {
    shdrt_ServiceContextMap map = {0};
    shdrt_Service calc = {.id = {.package = cstr_from("shd"), .name = cstr_from("calculator")},
                          .on_start_command = NULL,
                          .on_create = dummy_on_create,
                          .on_destroy = dummy_on_destroy,
                          .on_bind = NULL};
    shdrt_Service comm = {.id = {.package = cstr_from("shd"), .name = cstr_from("communication")},
                          .on_start_command = NULL,
                          .on_create = dummy_on_create,
                          .on_destroy = dummy_on_destroy,
                          .on_bind = NULL};
    shdrt_Service sett = {.id = {.package = cstr_from("shd"), .name = cstr_from("settings")},
                          .on_start_command = NULL,
                          .on_create = dummy_on_create,
                          .on_destroy = dummy_on_destroy,
                          .on_bind = NULL};
    shdrt_Service thirdp = {.id = {.package = cstr_from("acme"), .name = cstr_from("banking")},
                            .on_start_command = NULL,
                            .on_create = dummy_on_create,
                            .on_destroy = dummy_on_destroy,
                            .on_bind = NULL};

    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_create(&map, calc, NULL, NULL));
    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_create(&map, comm, NULL, NULL));
    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_create(&map, sett, NULL, NULL));
    TEST_ASSERT_NOT_NULL(shdrt_ServiceContextMap_create(&map, thirdp, NULL, NULL));

    TEST_ASSERT_TRUE(shdrt_ServiceContextMap_destroy(&map, calc));
    TEST_ASSERT_TRUE(shdrt_ServiceContextMap_destroy(&map, comm));
    TEST_ASSERT_TRUE(shdrt_ServiceContextMap_destroy(&map, sett));
    TEST_ASSERT_TRUE(shdrt_ServiceContextMap_destroy(&map, thirdp));

    TEST_ASSERT_FALSE(shdrt_ServiceContextMap_destroy(&map, calc));

    TEST_ASSERT_NULL(shdrt_ServiceContextMap_get(&map, calc));
    TEST_ASSERT_NULL(shdrt_ServiceContextMap_get(&map, comm));
    TEST_ASSERT_NULL(shdrt_ServiceContextMap_get(&map, sett));
    TEST_ASSERT_NULL(shdrt_ServiceContextMap_get(&map, thirdp));
}

int
main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_add);
    RUN_TEST(test_add_multiple);

    RUN_TEST(test_delete);
    RUN_TEST(test_delete_multiple);

    return UNITY_END();
}
