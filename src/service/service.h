#pragma once

#include <stc/cstr.h>

#include "../component_id.h"
#include "../intent/intent.h"

#include "binder.h"
#include "context.h"
#include "continuation_mode.h"
#include "start_flags.h"
#include "start_id.h"

/**
 * @struct shdrt_Service
 * @brief Represents a service component and its lifecycle callbacks.
 * 
 * Services are components that run in the background to perform long-running operations
 * or to perform work for remote processes.
 */
typedef struct {
    /**
     * @brief Unique identifier for this service component.
     */
    shdrt_ComponentIdentifier id;

    /**
     * @brief Called when the service is started.
     * 
     * @param context The service context.
     * @param intent The intent that started the service.
     * @param flags Additional data about this start request.
     * @param startId A unique integer representing this specific request to start.
     * @return The continuation mode (e.g., sticky or non-sticky).
     */
    shdrt_ServiceContinuationMode (*on_start_command)(shdrt_ServiceContext* context, shdrt_Intent intent,
                                                      shdrt_ServiceStartFlags flags, shdrt_ServiceStartId startId);

    /**
     * @brief Called when the service is first created.
     * 
     * @param context The service context.
     * @return true if initialization was successful, false otherwise.
     */
    bool (*on_create)(shdrt_ServiceContext* context);

    /**
     * @brief Called when the service is no longer used and is being destroyed.
     * 
     * @param context The service context.
     */
    void (*on_destroy)(shdrt_ServiceContext* context);

    /**
     * @brief Called when a client binds to the service with an intent.
     * 
     * @param intent The intent used to bind.
     * @return A binder object that clients can use to interact with the service.
     */
    shdrt_ServiceBinder* (*on_bind)(shdrt_Intent intent);

    /**
     * @brief Called when all clients have disconnected from a particular interface.
     * 
     * @param intent The intent that was used to bind.
     * @return true if you would like to have on_rebind called when new clients bind to it.
     */
    bool (*on_unbind)(shdrt_Intent intent);

    /**
     * @brief Called when new clients have connected to the service, after it had previously been notified that all had disconnected in on_unbind.
     * 
     * @param intent The intent used to bind.
     * @return A binder object.
     */
    shdrt_ServiceBinder* (*on_rebind)(shdrt_Intent intent);
} shdrt_Service;

int shdrt_Service_cmp(const shdrt_Service* a, const shdrt_Service* b);
bool shdrt_Service_equals(const shdrt_Service* a, const shdrt_Service* b);
