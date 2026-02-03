#include <fcntl.h>
#include <mqueue.h>
#include <unity.h>

#include "../src/worker/worker.h"
#include "stc/sys/sumtype.h"
#include "unity_internals.h"

void
setUp(void) {}

void
tearDown(void) {}

void
test_worker() {
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

    shdrt_worker_create(id, shdrt_package_identifier_make("shd.calculator"));
    shdrt_worker_send_message(id, message);

    printf("before receive\n");
    bytes = mq_receive(mq_results, (char*)&returned, sizeof(returned), NULL);
    TEST_ASSERT_TRUE(bytes > 0);
    c_when(&returned) {
        c_is(shdrt_worker_message_job) { TEST_FAIL_MESSAGE("Returned message was a job not a result!"); }
        c_is(shdrt_worker_message_result, result) {
            TEST_ASSERT_TRUE(result->id == message_id);
            c_when(&result->result) {
                c_is(shdrt_worker_result_stop_service) {
                    TEST_FAIL_MESSAGE("Returned result message was stop service not start service!");
                }
                c_is(shdrt_worker_result_start_service, result) { TEST_ASSERT_TRUE(result); }
            }
        }
    }
}

int
main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_worker);

    return UNITY_END();
}
