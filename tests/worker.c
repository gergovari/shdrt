#include <fcntl.h>
#include <mqueue.h>
#include <unistd.h>
#include <unity.h>

#include "../src/worker/worker.h"
#include "stc/common.h"
#include "stc/sys/sumtype.h"
#include "unity_internals.h"

void
setUp(void) {}

void
tearDown(void) {}

void
test_worker() {
    bool destroyed = false;
    bool started = false;

    bool is_created;
    ssize_t bytes;
    shdrt_worker_id_t id = 0;
    shdrt_worker_message_id_t message_id = 0;
    shdrt_worker_message_t message = c_variant(
        shdrt_worker_message_job,
        {.id = message_id,
         .job = c_variant(shdrt_worker_job_start_service,
                          {.id = shdrt_ComponentIdentifier_make("shd.calculator", "cumulate"), .intent = {}})});
    shdrt_worker_message_t returned;
    struct mq_attr attr = {.mq_maxmsg = 10, .mq_msgsize = sizeof(returned)};
    mqd_t mq_results;

    mq_unlink(SHDRT_WORKER_MQ_OUT_NAME);
    mq_results = mq_open(SHDRT_WORKER_MQ_OUT_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    TEST_ASSERT_FALSE(mq_results == -1);

    c_with(is_created = shdrt_worker_create(id, shdrt_package_identifier_make("shd.calculator")), is_created,
           shdrt_worker_destroy(id)) {
        shdrt_worker_send_message(id, message);

        bytes = mq_receive(mq_results, (char*)&returned, sizeof(returned), NULL);
        TEST_ASSERT_TRUE(bytes > 0);
        c_when(&returned) {
            c_is(shdrt_worker_message_job) { TEST_FAIL_MESSAGE("Returned message was a job not a result!"); }
            c_is(shdrt_worker_message_result, message) {
                TEST_ASSERT_TRUE(message->id == message_id);
                c_when(&message->result) {
                    c_is(shdrt_worker_result_destroy) {
                        TEST_FAIL_MESSAGE("Returned result message was stop service not start service!");
                    }
                    c_is(shdrt_worker_result_start_service, result) {
                        TEST_ASSERT_TRUE(result);
                        started = true;
                    }
                    c_is(shdrt_worker_result_stop_service) {
                        TEST_FAIL_MESSAGE("Returned result message was stop service not start service!");
                    }
                }
            }
        }
    }
    TEST_ASSERT_TRUE(is_created);

    bytes = mq_receive(mq_results, (char*)&returned, sizeof(returned), NULL);
    TEST_ASSERT_TRUE(bytes > 0);
    c_when(&returned) {
        c_is(shdrt_worker_message_job) { TEST_FAIL_MESSAGE("Returned message was a job not a result!"); }
        c_is(shdrt_worker_message_result, message) {
            TEST_ASSERT_TRUE(message->id == SHDRT_WORKER_ID_LAST);
            c_when(&message->result) {
                c_is(shdrt_worker_result_destroy) { destroyed = true; }
                c_is(shdrt_worker_result_start_service, result) {
                    TEST_FAIL_MESSAGE("Returned result message was stop service not destroy!");
                }
                c_is(shdrt_worker_result_stop_service) {
                    TEST_FAIL_MESSAGE("Returned result message was stop service not destroy!");
                }
            }
        }
    }

    TEST_ASSERT_TRUE(started);
    TEST_ASSERT_TRUE(destroyed);
}

int
main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_worker);

    return UNITY_END();
}
