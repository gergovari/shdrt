/**
 * @file
 * @brief Map implementation for connection binders.
 */
#pragma once

#include "binder.h"
#include "connection.h"

#define T shdrt_ServiceConnectionBinderMap, shdrt_ServiceConnection*, shdrt_ServiceBinder*
#include <stc/sortedmap.h>
#undef T

/**
 * @brief Associates a connection with a binder.
 * @param map Pointer to the map.
 * @param conn The connection.
 * @param binder The binder.
 * @return true if added.
 */
bool shdrt_ServiceConnectionBinderMap_add(shdrt_ServiceConnectionBinderMap* map, shdrt_ServiceConnection* conn,
                                          const shdrt_ServiceBinder* binder);

/**
 * @brief Removes the binder association for a connection.
 * @param map Pointer to the map.
 * @param conn The connection to remove.
 * @return true if removed.
 */
bool shdrt_ServiceConnectionBinderMap_delete(shdrt_ServiceConnectionBinderMap* map, shdrt_ServiceConnection* conn);

/**
 * @brief Retrieves the binder associated with a connection.
 * @param map Pointer to the map.
 * @param conn The connection.
 * @return The binder or NULL.
 */
const shdrt_ServiceBinder* shdrt_ServiceConnectionBinderMap_get_binder(shdrt_ServiceConnectionBinderMap* map,
                                                                       shdrt_ServiceConnection* conn);
