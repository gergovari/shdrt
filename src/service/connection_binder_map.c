#include "connection_binder_map.h"

/**
 * @brief Adds a connection-binder pair.
 * @param map The map.
 * @param conn The connection key.
 * @param binder The binder value.
 * @return true if successful.
 */
bool
shdrt_ServiceConnectionBinderMap_add(shdrt_ServiceConnectionBinderMap* map, shdrt_ServiceConnection* conn,
                                     const shdrt_ServiceBinder* binder) {
    return shdrt_ServiceConnectionBinderMap_insert(map, conn, (shdrt_ServiceBinder*)binder).inserted;
}

/**
 * @brief Deletes a connection-binder pair.
 * @param map The map.
 * @param conn The connection key.
 * @return true if erased.
 */
bool
shdrt_ServiceConnectionBinderMap_delete(shdrt_ServiceConnectionBinderMap* map, shdrt_ServiceConnection* conn) {
    return shdrt_ServiceConnectionBinderMap_erase(map, conn);
}

/**
 * @brief Gets a binder for a connection.
 * 
 * Iterates linearly to find the key. 
 * @note This implementation seems to do a linear scan although it's a map. 
 * Ideally, it should use the map's lookup function if the key type is compatible.
 * 
 * @param map The map.
 * @param conn The connection key.
 * @return The binder or NULL.
 */
const shdrt_ServiceBinder*
shdrt_ServiceConnectionBinderMap_get_binder(shdrt_ServiceConnectionBinderMap* map, shdrt_ServiceConnection* conn) {
    // Optimization: Use shdrt_ServiceConnectionBinderMap_get if possible, but for now matching implementation behavior
    for (c_each_kv(c, binder, shdrt_ServiceConnectionBinderMap, *map)) {
        if (*c == conn) {
            return binder;
        }
    }

    return NULL;
}
