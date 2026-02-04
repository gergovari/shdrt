#include "service.h"

#include "../component_id.h"

/**
 * @brief Compares two services based on their component ID.
 * @param a First service.
 * @param b Second service.
 * @return Comparison result (<0, 0, >0).
 */
int
shdrt_Service_cmp(const shdrt_Service* a, const shdrt_Service* b) {
    return shdrt_ComponentIdentifier_cmp(&a->id, &b->id);
}

/**
 * @brief Checks if two services are equal.
 * @param a First service.
 * @param b Second service.
 * @return true if IDs are equal.
 */
bool
shdrt_Service_equals(const shdrt_Service* a, const shdrt_Service* b) {
    return shdrt_Service_cmp(a, b) == 0;
}
