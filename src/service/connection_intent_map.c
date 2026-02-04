#include "connection_intent_map.h"
#include "connection.h"

/**
 * @brief Adds a connection-intent association.
 * @param map The map.
 * @param conn The connection key.
 * @param intent The intent value.
 * @return true if successful.
 */
bool
shdrt_ServiceConnectionIntentMap_add(shdrt_ServiceConnectionIntentMap* map, shdrt_ServiceConnection* conn,
                                     shdrt_Intent intent) {
    return shdrt_ServiceConnectionIntentMap_insert(map, conn, intent).inserted;
}

/**
 * @brief Deletes a connection-intent association.
 * @param map The map.
 * @param conn The connection key.
 * @return true if erased.
 */
bool
shdrt_ServiceConnectionIntentMap_delete(shdrt_ServiceConnectionIntentMap* map, shdrt_ServiceConnection* conn) {
    return shdrt_ServiceConnectionIntentMap_erase(map, conn);
}

/**
 * @brief Gets the intent for a connection.
 * 
 * Iterates linearly to match the connection pointer/key.
 * @note Similar optimization note as other maps; linear scan bypasses map lookup.
 * 
 * @param map The map.
 * @param conn The connection key.
 * @param out Output buffer.
 * @return true if found.
 */
bool
shdrt_ServiceConnectionIntentMap_get_intent(shdrt_ServiceConnectionIntentMap* map, shdrt_ServiceConnection* conn,
                                            shdrt_Intent* out) {
    // Optimization opportunity
    for (c_each_kv(c, intent, shdrt_ServiceConnectionIntentMap, *map)) {
        if ((shdrt_ServiceConnection*)c == conn) {
            *out = *intent;
            return true;
        }
    }
    return false;
}
