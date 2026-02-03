#include "package.h"

#include <stc/algorithm.h>
#include <stc/common.h>
#include <sys/types.h>

#include "package_id.h"

static bool
shd_calculator_cumulate_on_create(shdrt_ServiceContext* ctx) {
    ctx->user = c_new(u_int64_t, 0);
    return true;
}

static void
shd_calculator_cumulate_on_destroy(shdrt_ServiceContext* ctx) {
    c_free(ctx->user, sizeof(u_int64_t));
}

static shdrt_ServiceContinuationMode
shd_calculator_cumulate_on_start_command(shdrt_ServiceContext* ctx, shdrt_Intent intent, shdrt_ServiceStartFlags flags,
                                         shdrt_ServiceStartId id) {
    (*((u_int64_t*)(ctx->user)))++;
    return shdrt_SERVICE_START_NOT_STICKY;
}

bool
shdrt_package_get_service(shdrt_package_t* this, shdrt_ComponentIdentifier id, shdrt_Service* s) {
    shdrt_service_list_iter result;

    c_find_if(shdrt_service_list, this->services, &result, shdrt_ComponentIdentifier_equals(&id, &value->id));

    if (result.ref) {
        *s = *result.ref;
        return true;
    } else {
        return false;
    }
}

shdrt_package_t*
shdrt_package_load(shdrt_package_identifier_t id) {
    shdrt_package_identifier_t id2 = shdrt_package_identifier_make("shd.calculator");

    if (shdrt_package_identifier_equals(&id, &id2)) {
        /* TODO: implement properly */
        return c_new(shdrt_package_t,
                     {.services = c_make(shdrt_service_list,
                                         {(shdrt_Service){
                                             .id = shdrt_ComponentIdentifier_make("shd.calculator", "cumulate"),
                                             .on_create = shd_calculator_cumulate_on_create,
                                             .on_destroy = shd_calculator_cumulate_on_destroy,
                                             .on_start_command = shd_calculator_cumulate_on_start_command,
                                         }})});
    } else {
        return NULL;
    }
}

void
shdrt_package_unload(shdrt_package_t* this) {
    c_free(this, sizeof(shdrt_package_t));
}