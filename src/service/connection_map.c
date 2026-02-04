#include "connection_map.h"

/**
 * @brief Adds a connection.
 * 
 * Creates a new set of connections for the service if none exists, or adds to the existing set.
 * 
 * @param map Pointer to the map.
 * @param s The service.
 * @param conn The connection.
 * @return true if added.
 */
bool
shdrt_ServiceConnectionMap_add(shdrt_ServiceConnectionMap* map, shdrt_Service s, shdrt_ServiceConnection* conn) {
    shdrt_ServiceConnectionSet set = shdrt_ServiceConnectionSet_with_capacity(1);
    shdrt_ServiceConnectionMap_value* val = shdrt_ServiceConnectionMap_get_mut(map, s);

    shdrt_ServiceConnectionSet_push(&set, conn);
    return val ? shdrt_ServiceConnectionSet_insert(&val->second, conn).inserted
               : shdrt_ServiceConnectionMap_insert(map, s, set).inserted;
}

/**
 * @brief Deletes a connection.
 * 
 * Iterates through all services to find the connection.
 * Complexity: O(N) where N is the number of services.
 * 
 * @param map Pointer to the map.
 * @param conn The connection to delete.
 * @return true if deleted.
 */
bool
shdrt_ServiceConnectionMap_delete(shdrt_ServiceConnectionMap* map, shdrt_ServiceConnection* conn) {
    for (c_each_kv(s, set, shdrt_ServiceConnectionMap, *map)) {
        if (shdrt_ServiceConnectionSet_erase(set, conn)) {
            if (shdrt_ServiceConnectionSet_size(set) == 0) {
                shdrt_ServiceConnectionMap_erase(map, *s);
            }
            return true;
        }
    }

    return false;
}

bool
shdrt_ServiceConnectionMap_is_bound(shdrt_ServiceConnectionMap* map, shdrt_Service s) {
    return shdrt_ServiceConnectionMap_contains(map, s);
}

/**
 * @brief Reverse lookup to find a service by its connection.
 * @param map Pointer to the map.
 * @param conn Connection to search for.
 * @param out Output buffer for the service.
 * @return true if found.
 */
bool
shdrt_ServiceConnectionMap_get_service(shdrt_ServiceConnectionMap* map, shdrt_ServiceConnection* conn,
                                       shdrt_Service* out) {
    for (c_each_kv(s, set, shdrt_ServiceConnectionMap, *map)) {
        if (shdrt_ServiceConnectionSet_contains(set, conn)) {
            *out = *s;
            return true;
        }
    }
    return false;
}
