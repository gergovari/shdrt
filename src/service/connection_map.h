#pragma once

#include "service.h"
#include "connection.h"

#define T shdrt_ServiceConnectionSet, shdrt_ServiceConnection*
#include <stc/sortedset.h>
#undef T

#define T shdrt_ServiceConnectionMap, shdrt_Service, shdrt_ServiceConnectionSet
#define i_cmp shdrt_Service_cmp
#include <stc/sortedmap.h>
#undef T

bool shdrt_ServiceConnectionMap_add(shdrt_ServiceConnectionMap* map, shdrt_Service s, shdrt_ServiceConnection* conn);
bool shdrt_ServiceConnectionMap_delete(shdrt_ServiceConnectionMap* map, shdrt_ServiceConnection* conn);

bool shdrt_ServiceConnectionMap_is_bound(shdrt_ServiceConnectionMap* map, shdrt_Service s);
bool shdrt_ServiceConnectionMap_get_service(shdrt_ServiceConnectionMap* map, shdrt_ServiceConnection* conn, shdrt_Service* out);
