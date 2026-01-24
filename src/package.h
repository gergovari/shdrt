#pragma once

#include "component_id.h"
#include "package_id.h"
#include "service/service.h" // IWYU pragma: keep

#define T shdrt_service_list, shdrt_Service
#include <stc/list.h>
#undef T

typedef struct shdrt_package {
    shdrt_service_list services;
} shdrt_package_t;

shdrt_package_t* shdrt_package_load(shdrt_package_identifier_t id);
void shdrt_package_unload(shdrt_package_t* this);

bool shdrt_package_get_service(shdrt_package_t* this, shdrt_ComponentIdentifier id, shdrt_Service* s);