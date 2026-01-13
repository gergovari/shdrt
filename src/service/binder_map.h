#pragma once

#include "service.h"
#include "connection.h"

#define T shdrt_ServiceIntentBinderMap, shdrt_Intent, shdrt_ServiceBinder*
#define i_cmp shdrt_Intent_cmp
#include <stc/sortedmap.h>
#undef T

#define T shdrt_ServiceBinderMap, shdrt_Service, shdrt_ServiceIntentBinderMap
#define i_cmp shdrt_Service_cmp
#include <stc/sortedmap.h>
#undef T

// TODO

//bool shdrt_ServiceConnectionMap_add(shdrt_ServiceConnectionMap* map, shdrt_Service s, shdrt_ServiceConnection* conn);
//bool shdrt_ServiceConnectionMap_delete(shdrt_ServiceConnectionMap* map, shdrt_ServiceConnection* conn);
