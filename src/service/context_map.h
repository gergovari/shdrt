/**
 * @file
 * @brief Map implementation for service contexts.
 */
#pragma once

#include "context.h"
#include "service.h"
#include "stop_callback.h"

#define T     shdrt_ServiceContextMap, shdrt_Service, shdrt_ServiceContext*
#define i_cmp shdrt_Service_cmp
#include <stc/sortedmap.h>
#undef T

typedef struct shdrt_ServiceManager shdrt_ServiceManager;

/**
 * @brief Creates a service context for a given service.
 * 
 * If the context already exists, it is returned. Otherwise, a new one is allocated
 * and the service's @p on_create callback is invoked.
 * 
 * @param map Pointer to the map.
 * @param s The service.
 * @param man Pointer to the service manager.
 * @param stop Callback to stop the service.
 * @return The service context, or NULL on failure.
 */
shdrt_ServiceContext* shdrt_ServiceContextMap_create(shdrt_ServiceContextMap* map, shdrt_Service s,
                                                     shdrt_ServiceManager* man, shdrt_ServiceStopCallback stop);

/**
 * @brief Destroys a service context.
 * 
 * Invokes the service's @p on_destroy callback and frees the context memory.
 * 
 * @param map Pointer to the map.
 * @param s The service whose context should be destroyed.
 * @return true if found and destroyed, false otherwise.
 */
bool shdrt_ServiceContextMap_destroy(shdrt_ServiceContextMap* map, shdrt_Service s);

/**
 * @brief Checks if a service context exists.
 * @param map Pointer to the map.
 * @param s The service.
 * @return true if the context exists.
 */
bool shdrt_ServiceContextMap_is_created(shdrt_ServiceContextMap* map, shdrt_Service s);
