#pragma once

#include "../component_id.h"
#include "binder.h"

/**
 * @struct shdrt_ServiceConnection
 * @brief Callbacks for service connection events.
 * 
 * Implement this interface to receive notifications when a service is connected or disconnected.
 */
typedef struct shdrt_ServiceConnection {
    /**
     * @brief Called when the connection to the service has been lost.
     * 
     * This typically happens if the process hosting the service has crashed or been killed.
     * The service connection itself remains active, and you will receive a call to
     * @ref on_service_connected when the service is next running.
     * 
     * @param id The component identifier of the service.
     */
    void (*on_binding_died)(shdrt_ComponentIdentifier id);

    /**
     * @brief Called if the service was not found or could not be bound.
     * 
     * @param id The component identifier of the service.
     */
    void (*on_null_binding)(shdrt_ComponentIdentifier id);

    /**
     * @brief Called when a connection to the Service has been lost.
     * 
     * This typically happens when the process hosting the service has crashed or been killed.
     * This does *not* remove the ServiceConnection itself -- this binding to the service will remain active,
     * and you will receive a call to on_service_connected when the Service is next running.
     * 
     * @param id The component identifier of the service.
     */
    void (*on_service_disconnected)(shdrt_ComponentIdentifier id);

    /**
     * @brief Called when a connection to the Service has been established.
     * 
     * @param id The component identifier of the service.
     * @param binder The binder object used to interact with the service.
     */
    void (*on_service_connected)(shdrt_ComponentIdentifier id, const shdrt_ServiceBinder* binder);
} shdrt_ServiceConnection;
