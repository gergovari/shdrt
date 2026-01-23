#include "context_map.h"

shdrt_ServiceContext *
shdrt_ServiceContextMap_create(shdrt_ServiceContextMap *map, shdrt_Service s,
                               shdrt_ServiceManager *man,
                               shdrt_ServiceStopCallback stop) {
  shdrt_ServiceContext *ctx;
  shdrt_ServiceContextMap_result res;
  const shdrt_ServiceContextMap_value *val =
      shdrt_ServiceContextMap_get(map, s);

  if (val)
    return val->second;

  ctx = c_new(shdrt_ServiceContext,
              {.continuation_mode = 0, .stop = stop, .man = man});
  res = shdrt_ServiceContextMap_insert(map, s, ctx);

  if (!res.inserted)
    return NULL;
  return s.on_create(ctx) ? ctx : NULL;
}

bool shdrt_ServiceContextMap_destroy(shdrt_ServiceContextMap *map,
                                     shdrt_Service s) {
  const shdrt_ServiceContextMap_value *val =
      shdrt_ServiceContextMap_get(map, s);
  shdrt_ServiceContext *ctx;

  if (!val)
    return false;
  ctx = val->second;

  s.on_destroy(ctx);
  shdrt_ServiceContextMap_erase(map, s);
  c_free(ctx, sizeof(shdrt_ServiceContext));
  return true;
}

bool shdrt_ServiceContextMap_is_created(shdrt_ServiceContextMap *map,
                                        shdrt_Service s) {
  return shdrt_ServiceContextMap_contains(map, s);
}
