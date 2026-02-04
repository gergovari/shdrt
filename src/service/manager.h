#pragma once

#include "context_map.h"
#include "start_id_map.h"

#include "../intent/intent.h"
#include "service.h"

/**
 * @struct shdrt_ServiceManager
 * @brief Manages the lifecycle and connections of services.
 * 
 * The Service Manager is responsible for starting, stopping, and tracking
 * active services. It maintains maps of created services and their start IDs.
 */
typedef struct shdrt_ServiceManager {
    /**
     * @brief Map of created service contexts.
     */
    shdrt_ServiceContextMap created;

    /**
     * @brief Map matching services to their start IDs.
     */
    shdrt_ServiceStartIdMap startIds;
} shdrt_ServiceManager;

typedef struct shdrt_ServiceConnection shdrt_ServiceConnection;

/**
 * @brief Creates a new Service Manager instance.
 * 
 * Initializes the internal maps for tracking services.
 * 
 * @return A new, initialized @ref shdrt_ServiceManager struct.
 */
shdrt_ServiceManager shdrt_ServiceManager_make();

/**
 * @brief Destroys a Service Manager instance and releases resources.
 * 
 * This function cleans up the internal maps and any resources held by the manager.
 * 
 * @param man Pointer to the @ref shdrt_ServiceManager to destroy.
 */
void shdrt_ServiceManager_drop(shdrt_ServiceManager* man);

/**
 * @brief Stops a service given its start ID.
 * 
 * @param man Pointer to the Service Manager.
 * @param id The start ID of the service to stop.
 * @return true if the service was found and stopped successfully, false otherwise.
 */
bool shdrt_ServiceManager_stop_self(shdrt_ServiceManager* man, shdrt_ServiceStartId id);

/**
 * @brief Starts a service with the given intent.
 * 
 * @param man Pointer to the Service Manager.
 * @param s The service identifier to start.
 * @param intent The intent describing how the service should be started.
 * @return true if the service was started successfully (or was already running), false otherwise.
 */
bool shdrt_ServiceManager_start(shdrt_ServiceManager* man, shdrt_Service s, shdrt_Intent intent);

/**
 * @brief Stops a specific service.
 * 
 * @param man Pointer to the Service Manager.
 * @param s The service identifier to stop.
 * @return true if the service was stopped successfully, false otherwise.
 */
bool shdrt_ServiceManager_stop(shdrt_ServiceManager* man, shdrt_Service s);

/*bool shdrt_ServiceManager_bind(shdrt_ServiceManager *man, shdrt_Service s,
                               shdrt_Intent intent,
                               shdrt_ServiceConnection *conn,
                               shdrt_ServiceBindBitset flags);
void shdrt_ServiceManager_unbind(shdrt_ServiceManager *man,
                                 shdrt_ServiceConnection *conn);*/
