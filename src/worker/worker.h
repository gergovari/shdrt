#pragma once

#include <mqueue.h>
#include <stdint.h>
#include <sys/types.h>

#include <stc/algorithm.h>
#include <stc/sys/sumtype.h>

#include "../component_id.h"
#include "../package/package.h"
#include "../package/package_id.h"
#include "../service/manager.h"

#define SHDRT_WORKER_MQ_OUT_NAME   "/result_queue"
#define SHDRT_WORKER_MQ_IN_FMT     "/worker_%" PRIu64 "_queue"
#define SHDRT_WORKER_MQ_IN_MAX_MSG 10

typedef u_int64_t shdrt_worker_id_t;

c_union(shdrt_worker_job_t,
        (
            shdrt_worker_job_start_service,
            struct {
                shdrt_ComponentIdentifier id;
                shdrt_Intent intent;
            }),
        (shdrt_worker_job_stop_service, shdrt_ComponentIdentifier), );

c_union(shdrt_worker_result_t, (shdrt_worker_result_start_service, bool), (shdrt_worker_result_stop_service, bool), );

typedef u_int64_t shdrt_worker_message_id_t;
c_union(shdrt_worker_message_t,
        (
            shdrt_worker_message_job,
            struct {
                shdrt_worker_message_id_t id;
                shdrt_worker_job_t job;
            }),
        (
            shdrt_worker_message_result, struct {
                shdrt_worker_message_id_t id;
                shdrt_worker_result_t result;
            }), );

typedef struct shdrt_worker {
    shdrt_worker_id_t id;
    shdrt_package_t* package;

    shdrt_ServiceManager service_manager;

    mqd_t in;
    mqd_t out;
} shdrt_worker_t;

void shdrt_worker_create(shdrt_worker_id_t id, shdrt_package_identifier_t package_id);
void shdrt_worker_send_message(shdrt_worker_id_t id, shdrt_worker_message_t message);
