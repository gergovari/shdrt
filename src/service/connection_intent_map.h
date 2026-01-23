#pragma once

#include "../intent/intent.h"
#include "connection.h"

#define T                                                                      \
  shdrt_ServiceConnectionIntentMap, shdrt_ServiceConnection *, shdrt_Intent
#include <stc/sortedmap.h>
#undef T

bool shdrt_ServiceConnectionIntentMap_add(shdrt_ServiceConnectionIntentMap *map,
                                          shdrt_ServiceConnection *conn,
                                          shdrt_Intent intent);
bool shdrt_ServiceConnectionIntentMap_delete(
    shdrt_ServiceConnectionIntentMap *map, shdrt_ServiceConnection *conn);

bool shdrt_ServiceConnectionIntentMap_get_intent(
    shdrt_ServiceConnectionIntentMap *map, shdrt_ServiceConnection *conn,
    shdrt_Intent *out);
