#include "binder_map.h"

/**
 * @brief Adds a binder to the map.
 * 
 * Creates a nested map if one does not exist for the service.
 * 
 * @param map Pointer to the map.
 * @param s The service.
 * @param intent The intent.
 * @param binder The binder to add.
 * @return true if added successfully.
 */
bool
shdrt_ServiceBinderMap_add(shdrt_ServiceBinderMap* map, shdrt_Service s, shdrt_Intent intent,
                           const shdrt_ServiceBinder* binder) {
    shdrt_ServiceBinderMap_iter it = shdrt_ServiceBinderMap_find(map, s);

    if (it.ref == NULL) {
        shdrt_ServiceIntentBinderMap inner = shdrt_ServiceIntentBinderMap_init();
        shdrt_ServiceBinderMap_result res = shdrt_ServiceBinderMap_insert(map, s, inner);

        if (!res.inserted) {
            return false;
        }

        it.ref = res.ref;
    }

    shdrt_ServiceIntentBinderMap_result res =
        shdrt_ServiceIntentBinderMap_insert_or_assign(&it.ref->second, intent, (shdrt_ServiceBinder*)binder);

    return res.inserted;
}

/**
 * @brief Removes a service's binders from the map.
 * @param map Pointer to the map.
 * @param s The service to remove.
 * @return true if removed.
 */
bool
shdrt_ServiceBinderMap_delete(shdrt_ServiceBinderMap* map, shdrt_Service s) {
    return shdrt_ServiceBinderMap_erase(map, s);
}

/**
 * @brief Gets a binder for a service and intent.
 * @param map Pointer to the map.
 * @param s The service.
 * @param intent The intent.
 * @return The binder or NULL.
 */
const shdrt_ServiceBinder*
shdrt_ServiceBinderMap_get_binder(shdrt_ServiceBinderMap* map, shdrt_Service s, shdrt_Intent intent) {
    const shdrt_ServiceBinderMap_value* val = shdrt_ServiceBinderMap_get(map, s);

    if (!val) {
        return NULL;
    }
    return shdrt_ServiceIntentBinderMap_get(&val->second, intent);
}
