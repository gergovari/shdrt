#include "package.h"

#include "stc/common.h"

bool
shdrt_package_get_service(shdrt_package_t* this, shdrt_ComponentIdentifier id, shdrt_Service* s) {
    /* TODO: implement */
    return false;
}

shdrt_package_t*
shdrt_package_load(shdrt_package_identifier_t id) {
    /* TODO: implement */
    return NULL;
}

void
shdrt_package_unload(shdrt_package_t* this) {
    c_free(this, sizeof(shdrt_package_t));
}