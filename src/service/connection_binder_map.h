#pragma once

#include "binder.h"
#include "connection.h"

#define T                                                                      \
  shdrt_ServiceConnectionBinderMap, shdrt_ServiceConnection *,                 \
      shdrt_ServiceBinder *
#include <stc/sortedmap.h>
#undef T

bool shdrt_ServiceConnectionBinderMap_add(shdrt_ServiceConnectionBinderMap *map,
                                          shdrt_ServiceConnection *conn,
                                          const shdrt_ServiceBinder *binder);
bool shdrt_ServiceConnectionBinderMap_delete(
    shdrt_ServiceConnectionBinderMap *map, shdrt_ServiceConnection *conn);

const shdrt_ServiceBinder *shdrt_ServiceConnectionBinderMap_get_binder(
    shdrt_ServiceConnectionBinderMap *map, shdrt_ServiceConnection *conn);
