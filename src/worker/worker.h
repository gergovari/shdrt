#pragma once

#include <mqueue.h>
#include <stdint.h>
#include <sys/types.h>

#include <stc/algorithm.h>
#include <stc/sys/sumtype.h>

#include "../package/package.h"
#include "../package/package_id.h"
#include "../service/manager.h"

#define SHDRT_WORKER_MQ_OUT_NAME   "/result_queue"
#define SHDRT_WORKER_MQ_IN_FMT     "/worker_%" PRIu64 "_queue"
#define SHDRT_WORKER_MQ_IN_MAX_MSG 10

/**
 * @typedef shdrt_worker_id_t
 * @brief Unique identifier for a worker process.
 */
typedef int64_t shdrt_worker_id_t;
#define SHDRT_WORKER_ID_LAST -1

/**
 * @typedef shdrt_worker_job_t
 * @brief Sum-type representing a job to be executed by a worker.
 */
c_union(shdrt_worker_job_t,
        /** @brief Instructs the worker to destroy itself. */
        (shdrt_worker_job_destroy, void*),
        /** @brief Instructs the worker to start a service. */
        (
            shdrt_worker_job_start_service,
            struct {
                shdrt_ComponentIdentifier id;
                shdrt_Intent intent;
            }),
        /** @brief Instructs the worker to stop a service. */
        (shdrt_worker_job_stop_service, shdrt_ComponentIdentifier), );

/**
 * @typedef shdrt_worker_result_t
 * @brief Sum-type representing the result of a worker job.
 */
c_union(shdrt_worker_result_t, (shdrt_worker_result_destroy, void*), (shdrt_worker_result_start_service, bool),
        (shdrt_worker_result_stop_service, bool), );

/**
 * @typedef shdrt_worker_message_id_t
 * @brief Unique identifier for a message sent to/from a worker.
 */
typedef u_int64_t shdrt_worker_message_id_t;

/**
 * @typedef shdrt_worker_message_t
 * @brief Sum-type representing a message passed between the main process and a worker.
 */
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

/**
 * @struct shdrt_worker
 * @brief Represents a worker process and its state.
 */
typedef struct shdrt_worker {
    shdrt_worker_id_t id;
    shdrt_package_t* package;

    shdrt_ServiceManager service_manager;

    mqd_t in;
    mqd_t out;
} shdrt_worker_t;

/**
 * @brief Creates a new worker process.
 * 
 * Forks the current process to create a new worker that loads the specified package.
 * 
 * @param id The unique ID to assign to the new worker.
 * @param package_id The identifier of the package to load in the worker.
 * @return true if the worker was successfully created (in the parent process), false otherwise.
 * @note This function forks. The child process will enter the worker loop.
 */
bool shdrt_worker_create(shdrt_worker_id_t id, shdrt_package_identifier_t package_id);

/**
 * @brief Destroys a worker process.
 * 
 * Sends a destroy message to the worker, causing it to exit.
 * 
 * @param id The ID of the worker to destroy.
 * @todo Refactor return type to bool to indicate success/failure.
 */
void shdrt_worker_destroy(shdrt_worker_id_t id);

/**
 * @brief Sends a message to a specific worker.
 * 
 * @param id The ID of the target worker.
 * @param message The message to send.
 */
void shdrt_worker_send_message(shdrt_worker_id_t id, shdrt_worker_message_t message);
