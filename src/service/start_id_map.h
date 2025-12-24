#pragma once

#include "start_id.h"
#include "service.h"

#define T shdrt_ServiceStartIdMap, shdrt_ServiceStartId, shdrt_Service
#include <stc/sortedmap.h>
#undef T

bool shdrt_ServiceStartIdMap_start(shdrt_ServiceStartIdMap* map, shdrt_Service s, shdrt_ServiceStartId* id);
bool shdrt_ServiceStartIdMap_stop(shdrt_ServiceStartIdMap* map, shdrt_ServiceStartId id);
bool shdrt_ServiceStartIdMap_get_service(shdrt_ServiceStartIdMap* map, shdrt_ServiceStartId id, shdrt_Service* out);
void shdrt_ServiceStartIdMap_forget(shdrt_ServiceStartIdMap* map, shdrt_Service s);
