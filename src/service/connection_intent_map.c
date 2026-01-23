#include "connection_intent_map.h"

bool shdrt_ServiceConnectionIntentMap_add(shdrt_ServiceConnectionIntentMap *map,
                                          shdrt_ServiceConnection *conn,
                                          shdrt_Intent intent) {
  return shdrt_ServiceConnectionIntentMap_insert(map, conn, intent).inserted;
}

bool shdrt_ServiceConnectionIntentMap_delete(
    shdrt_ServiceConnectionIntentMap *map, shdrt_ServiceConnection *conn) {
  return shdrt_ServiceConnectionIntentMap_erase(map, conn);
}

bool shdrt_ServiceConnectionIntentMap_get_intent(
    shdrt_ServiceConnectionIntentMap *map, shdrt_ServiceConnection *conn,
    shdrt_Intent *out) {
  for (c_each_kv(c, intent, shdrt_ServiceConnectionIntentMap, *map)) {
    if (c == conn) {
      *out = *intent;
      return true;
    }
  }
  return false;
}
