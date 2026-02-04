#include "start_id_map.h"

#include <stdlib.h>

// TODO: why not just keep an increasing count?
/**
 * @brief Generates a unique random start ID.
 * @param map The map to check for collisions.
 * @return A unique unused ID.
 */
static int64_t
shdrt_ServiceStartIdMap_generate_id(shdrt_ServiceStartIdMap* map) {
    int64_t id = rand();

    while (shdrt_ServiceStartIdMap_get(map, id) != NULL) {
        id = rand();
    }
    return id;
}

/**
 * @brief Starts a service with a new ID.
 * @param map The map.
 * @param s The service.
 * @param id Output for the ID.
 * @return true if successful.
 */
bool
shdrt_ServiceStartIdMap_start(shdrt_ServiceStartIdMap* map, shdrt_Service s, shdrt_ServiceStartId* id) {
    shdrt_ServiceStartIdMap_result res =
        shdrt_ServiceStartIdMap_insert(map, shdrt_ServiceStartIdMap_generate_id(map), s);

    if (res.inserted) {
        *id = res.ref->first;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Stops a start ID and checks if service should stop.
 * 
 * Checks if there are any other start IDs pointing to the same service.
 * 
 * @param map The map.
 * @param id The ID to stop.
 * @return true if this was the last ID for the service.
 */
bool
shdrt_ServiceStartIdMap_stop(shdrt_ServiceStartIdMap* map, shdrt_ServiceStartId id) {
    const shdrt_ServiceStartIdMap_value* val = shdrt_ServiceStartIdMap_get(map, id);
    if (!val) {
        return false;
    }

    shdrt_ServiceStartIdMap_iter i = shdrt_ServiceStartIdMap_find(map, id);

    // Check forward
    shdrt_ServiceStartIdMap_next(&i);
    while (i.ref) {
        if (shdrt_Service_equals(&i.ref->second, &val->second)) {
            return false;
        }
        shdrt_ServiceStartIdMap_next(&i);
    }

    // TODO: This logic only checks forward from the found ID?
    // It seems to imply the map might be sorted by service or that we rely on random distribution?
    // If the map is sorted by ID (int64), services are scattered.
    // This check seems insufficient if services are scattered and we only check "next".
    // However, documenting behavior as implemented.

    shdrt_ServiceStartIdMap_erase(map, id);
    return true;
}

bool
shdrt_ServiceStartIdMap_get_service(shdrt_ServiceStartIdMap* map, shdrt_ServiceStartId id, shdrt_Service* out) {
    const shdrt_ServiceStartIdMap_value* val = shdrt_ServiceStartIdMap_get(map, id);

    if (val) {
        *out = val->second;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Removes all start IDs for a service.
 * 
 * Iterates through the entire map.
 * 
 * @param map The map.
 * @param s The service.
 */
void
shdrt_ServiceStartIdMap_forget(shdrt_ServiceStartIdMap* map, shdrt_Service s) {
    shdrt_ServiceStartIdMap_iter i = shdrt_ServiceStartIdMap_begin(map);

    while (i.ref) {
        if (shdrt_Service_equals(&i.ref->second, &s)) {
            i = shdrt_ServiceStartIdMap_erase_at(map, i);
        } else {
            shdrt_ServiceStartIdMap_next(&i);
        }
    }
}
