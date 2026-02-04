/**
 * @file
 * @brief Maps services and intents to binders.
 */

#pragma once

#include "service.h"

#define T     shdrt_ServiceIntentBinderMap, shdrt_Intent, shdrt_ServiceBinder*
#define i_cmp shdrt_Intent_cmp
#include <stc/sortedmap.h>
#undef T

#define T     shdrt_ServiceBinderMap, shdrt_Service, shdrt_ServiceIntentBinderMap
#define i_cmp shdrt_Service_cmp
#include <stc/sortedmap.h>
#undef T

/**
 * @brief Adds a binder to the map for a given service and intent.
 * 
 * @param map Pointer to the map.
 * @param s The service associated with the binder.
 * @param intent The intent used to bind.
 * @param binder The binder object.
 * @return true if added successfully, false otherwise.
 */
bool shdrt_ServiceBinderMap_add(shdrt_ServiceBinderMap* map, shdrt_Service s, shdrt_Intent intent,
                                const shdrt_ServiceBinder* binder);

/**
 * @brief Removes all binders associated with a service from the map.
 * 
 * @param map Pointer to the map.
 * @param s The service to remove.
 * @return true if the service was found and removed, false otherwise.
 */
bool shdrt_ServiceBinderMap_delete(shdrt_ServiceBinderMap* map, shdrt_Service s);

/**
 * @brief Retrieves a binder for a specific service and intent.
 * 
 * @param map Pointer to the map.
 * @param s The service to look up.
 * @param intent The intent used to bind.
 * @return The binder object, or NULL if not found.
 */
const shdrt_ServiceBinder* shdrt_ServiceBinderMap_get_binder(shdrt_ServiceBinderMap* map, shdrt_Service s,
                                                             shdrt_Intent intent);
