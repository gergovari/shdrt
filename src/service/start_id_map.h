/**
 * @file
 * @brief Map implementation for service start IDs.
 */
#pragma once

#include "service.h"
#include "start_id.h"

#define T shdrt_ServiceStartIdMap, shdrt_ServiceStartId, shdrt_Service
#include <stc/sortedmap.h>
#undef T

/**
 * @brief Generates a new start ID for a service and maps it.
 * @param map Pointer to the map.
 * @param s The service being started.
 * @param id Output pointer for the generated ID.
 * @return true if successful.
 */
bool shdrt_ServiceStartIdMap_start(shdrt_ServiceStartIdMap* map, shdrt_Service s, shdrt_ServiceStartId* id);

/**
 * @brief Stops a specific start ID.
 * 
 * If this is the last active start ID for the associated service, returns true.
 * If there are other active start IDs for the service, returns false (meaning the service should stay running).
 * 
 * @param map Pointer to the map.
 * @param id The start ID to stop.
 * @return true if the service should be stopped (last ID removed), false otherwise.
 */
bool shdrt_ServiceStartIdMap_stop(shdrt_ServiceStartIdMap* map, shdrt_ServiceStartId id);

/**
 * @brief Retrieves the service associated with a start ID.
 * @param map Pointer to the map.
 * @param id The start ID.
 * @param out Output buffer for the service.
 * @return true if found.
 */
bool shdrt_ServiceStartIdMap_get_service(shdrt_ServiceStartIdMap* map, shdrt_ServiceStartId id, shdrt_Service* out);

/**
 * @brief Removes all start IDs associated with a service.
 * @param map Pointer to the map.
 * @param s The service to forget.
 */
void shdrt_ServiceStartIdMap_forget(shdrt_ServiceStartIdMap* map, shdrt_Service s);
