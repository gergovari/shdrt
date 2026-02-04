/**
 * @file
 * @brief Map implementation for service connections.
 */
#pragma once

#include "connection.h"
#include "service.h"

#define T shdrt_ServiceConnectionSet, shdrt_ServiceConnection*
#include <stc/sortedset.h>
#undef T

#define T     shdrt_ServiceConnectionMap, shdrt_Service, shdrt_ServiceConnectionSet
#define i_cmp shdrt_Service_cmp
#include <stc/sortedmap.h>
#undef T

/**
 * @brief Adds a connection to the map for a given service.
 * @param map Pointer to the map.
 * @param s The service.
 * @param conn The connection to add.
 * @return true if added successfully.
 */
bool shdrt_ServiceConnectionMap_add(shdrt_ServiceConnectionMap* map, shdrt_Service s, shdrt_ServiceConnection* conn);

/**
 * @brief Removes a connection from the map.
 * 
 * If the service has no more connections after removal, the service entry is also removed.
 * 
 * @param map Pointer to the map.
 * @param conn The connection to remove.
 * @return true if the connection was found and removed.
 */
bool shdrt_ServiceConnectionMap_delete(shdrt_ServiceConnectionMap* map, shdrt_ServiceConnection* conn);

/**
 * @brief Checks if a service is bound (has at least one connection).
 * @param map Pointer to the map.
 * @param s The service to check.
 * @return true if bound.
 */
bool shdrt_ServiceConnectionMap_is_bound(shdrt_ServiceConnectionMap* map, shdrt_Service s);

/**
 * @brief Retrieves the service associated with a specific connection.
 * @param map Pointer to the map.
 * @param conn The connection to look up.
 * @param out Pointer to store the found service.
 * @return true if found, false otherwise.
 */
bool shdrt_ServiceConnectionMap_get_service(shdrt_ServiceConnectionMap* map, shdrt_ServiceConnection* conn,
                                            shdrt_Service* out);
