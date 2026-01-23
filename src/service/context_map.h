#pragma once

#include "context.h"
#include "service.h"
#include "stop_callback.h"

#define T     shdrt_ServiceContextMap, shdrt_Service, shdrt_ServiceContext*
#define i_cmp shdrt_Service_cmp
#include <stc/sortedmap.h>
#undef T

typedef struct shdrt_ServiceManager shdrt_ServiceManager;

shdrt_ServiceContext* shdrt_ServiceContextMap_create(shdrt_ServiceContextMap* map, shdrt_Service s,
                                                     shdrt_ServiceManager* man, shdrt_ServiceStopCallback stop);
bool shdrt_ServiceContextMap_destroy(shdrt_ServiceContextMap* map, shdrt_Service s);

bool shdrt_ServiceContextMap_is_created(shdrt_ServiceContextMap* map, shdrt_Service s);
