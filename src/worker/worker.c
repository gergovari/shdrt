#include "worker.h"

#include <fcntl.h>
#include <mqueue.h>
#include <stdlib.h>
#include <unistd.h>

#include <stc/sys/sumtype.h>

#include "../package/package.h"
#include "../package/package_id.h"
#include "../service/manager.h"
#include "../service/service.h"

static ssize_t
shdrt_worker_mq_receive(shdrt_worker_t* this, shdrt_worker_message_t* msg_ptr) {
    return mq_receive(this->in, (char*)msg_ptr, sizeof(*msg_ptr), NULL);
}

static int
shdrt_worker_mq_send(shdrt_worker_t* this, shdrt_worker_message_t* msg_ptr) {
    return mq_send(this->out, (char*)msg_ptr, sizeof(*msg_ptr), 0);
}

static void
shdrt_worker_handle_job(shdrt_worker_t* this, shdrt_worker_job_t job, shdrt_worker_message_id_t id) {
    c_when(&job) {
        c_is(shdrt_worker_job_start_service, job) {
            shdrt_worker_result_start_service_type result = false;
            shdrt_Service s;

            if (shdrt_package_get_service(this->package, job->id, &s)) {
                result = shdrt_ServiceManager_start(&this->service_manager, s, job->intent);
            }

            shdrt_worker_message_t message = c_variant(shdrt_worker_message_result, {.id = id, .result = result});
            shdrt_worker_mq_send(this, &message);
        }
        c_is(shdrt_worker_job_stop_service, job) {
            shdrt_worker_result_start_service_type result = false;
            shdrt_Service s;

            if (shdrt_package_get_service(this->package, *job, &s)) {
                result = shdrt_ServiceManager_stop(&this->service_manager, s);
            }

            shdrt_worker_message_t message = c_variant(shdrt_worker_message_result, {.id = id, .result = result});
            shdrt_worker_mq_send(this, &message);
        }
    }
}

static void
shdrt_worker_receive_message(shdrt_worker_t* this) {
    shdrt_worker_message_t message;
    ssize_t bytes = shdrt_worker_mq_receive(this, &message);

    if (bytes > 0) {
        c_when(&message) {
            c_is(shdrt_worker_message_job, message) { shdrt_worker_handle_job(this, message->job, message->id); }
            c_is(shdrt_worker_message_result, message) { return; }
        }
    }
}

static bool
shdrt_worker_loop(shdrt_worker_t* this) {
    while (true) {
        shdrt_worker_receive_message(this);
    }
    return true;
}

static bool
shdrt_worker_is_initialized(const shdrt_worker_t* this) {
    return this->package && this->in >= 0 && this->out >= 0;
}

static void
shdrt_worker_name_from_id(char* name, shdrt_worker_id_t id) {
    sprintf(name, SHDRT_WORKER_MQ_IN_FMT, id);
}

static shdrt_worker_t
shdrt_worker_make(shdrt_worker_id_t id, shdrt_package_identifier_t package_id) {
    char name[64];
    struct mq_attr attr = {.mq_maxmsg = SHDRT_WORKER_MQ_IN_MAX_MSG, .mq_msgsize = sizeof(shdrt_worker_message_t)};

    mq_unlink(name);
    shdrt_worker_name_from_id((char*)&name, id);
    return (shdrt_worker_t){.id = id,
                            .service_manager = shdrt_ServiceManager_make(),
                            .package = shdrt_package_load(package_id),
                            .in = mq_open(name, O_CREAT | O_RDONLY, 0644, &attr),
                            .out = mq_open(SHDRT_WORKER_MQ_OUT_NAME, O_WRONLY)};
}

static void
shdrt_worker_drop(shdrt_worker_t* this) {
    shdrt_ServiceManager_drop(&this->service_manager);
    if (this->package != NULL) {
        shdrt_package_unload(this->package);
    }
    mq_close(this->in);
    mq_close(this->out);
}

void
shdrt_worker_create(shdrt_worker_id_t id, shdrt_package_identifier_t package_id) {
    if (fork() == 0) {
        int status = EXIT_SUCCESS;
        shdrt_worker_t this = shdrt_worker_make(id, package_id);

        if (shdrt_worker_is_initialized(&this)) {
            if (!shdrt_worker_loop(&this)) {
                status = EXIT_FAILURE;
            }
        } else {
            status = EXIT_FAILURE;
        }

        shdrt_worker_drop(&this);
        exit(status);
    }
}

void
shdrt_worker_send_message(shdrt_worker_id_t id, shdrt_worker_message_t message) {
    char name[64];
    mqd_t mqdes;

    shdrt_worker_name_from_id((char*)&name, id);
    mqdes = mq_open(name, O_WRONLY);

    mq_send(mqdes, (char*)&message, sizeof(message), 0);

    mq_close(mqdes);
}