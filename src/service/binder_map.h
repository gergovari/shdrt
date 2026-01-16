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

bool shdrt_ServiceBinderMap_add(shdrt_ServiceBinderMap* map, shdrt_Service s, shdrt_Intent intent, shdrt_ServiceBinder* binder);
bool shdrt_ServiceBinderMap_delete(shdrt_ServiceBinderMap* map, shdrt_Service s);
