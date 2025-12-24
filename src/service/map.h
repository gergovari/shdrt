#pragma once

#include "context.h"
#include "stop_callback.h"
#include "service.h"

#define T shdrt_ServiceMap, shdrt_Service, shdrt_ServiceContext*
#define i_cmp shdrt_Service_cmp
#include <stc/sortedmap.h>
#undef T

shdrt_ServiceContext* shdrt_ServiceMap_add(shdrt_ServiceMap* map, shdrt_Service s, void* user, shdrt_ServiceStopCallback stop);
bool shdrt_ServiceMap_delete(shdrt_ServiceMap* map, shdrt_Service s);
