/**
 * @file
 * @brief Map implementation for connection intents.
 */
#pragma once

#include "../intent/intent.h"
#include "connection.h"

#define T shdrt_ServiceConnectionIntentMap, shdrt_ServiceConnection*, shdrt_Intent
#include <stc/sortedmap.h>
#undef T

/**
 * @brief Associates a connection with the intent used to bind it.
 * @param map Pointer to the map.
 * @param conn The connection.
 * @param intent The intent.
 * @return true if added.
 */
bool shdrt_ServiceConnectionIntentMap_add(shdrt_ServiceConnectionIntentMap* map, shdrt_ServiceConnection* conn,
                                          shdrt_Intent intent);

/**
 * @brief Removes a connection's intent from the map.
 * @param map Pointer to the map.
 * @param conn The connection to remove.
 * @return true if removed.
 */
bool shdrt_ServiceConnectionIntentMap_delete(shdrt_ServiceConnectionIntentMap* map, shdrt_ServiceConnection* conn);

/**
 * @brief Retrieves the intent associated with a connection.
 * @param map Pointer to the map.
 * @param conn The connection to look up.
 * @param out Pointer to store the result intent.
 * @return true if found, false otherwise.
 */
bool shdrt_ServiceConnectionIntentMap_get_intent(shdrt_ServiceConnectionIntentMap* map, shdrt_ServiceConnection* conn,
                                                 shdrt_Intent* out);
