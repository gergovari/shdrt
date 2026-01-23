#include "start_id_map.h"

#include <stdlib.h>

// TODO: why not just keep an increasing count?
int64_t shdrt_ServiceStartIdMap_generate_id(shdrt_ServiceStartIdMap *map) {
  int64_t id = rand();

  while (shdrt_ServiceStartIdMap_get(map, id) != NULL)
    id = rand();
  return id;
}

bool shdrt_ServiceStartIdMap_start(shdrt_ServiceStartIdMap *map,
                                   shdrt_Service s, shdrt_ServiceStartId *id) {
  shdrt_ServiceStartIdMap_result res = shdrt_ServiceStartIdMap_insert(
      map, shdrt_ServiceStartIdMap_generate_id(map), s);

  if (res.inserted) {
    *id = res.ref->first;
    return true;
  } else
    return false;
}

bool shdrt_ServiceStartIdMap_stop(shdrt_ServiceStartIdMap *map,
                                  shdrt_ServiceStartId id) {
  const shdrt_ServiceStartIdMap_value *val =
      shdrt_ServiceStartIdMap_get(map, id);
  if (!val)
    return false;

  shdrt_ServiceStartIdMap_iter i = shdrt_ServiceStartIdMap_find(map, id);

  shdrt_ServiceStartIdMap_next(&i);
  while (i.ref) {
    if (shdrt_Service_equals(&i.ref->second, &val->second))
      return false;
    shdrt_ServiceStartIdMap_next(&i);
  }

  shdrt_ServiceStartIdMap_erase(map, id);
  return true;
}

bool shdrt_ServiceStartIdMap_get_service(shdrt_ServiceStartIdMap *map,
                                         shdrt_ServiceStartId id,
                                         shdrt_Service *out) {
  const shdrt_ServiceStartIdMap_value *val =
      shdrt_ServiceStartIdMap_get(map, id);

  if (val) {
    *out = val->second;
    return true;
  } else
    return false;
}

void shdrt_ServiceStartIdMap_forget(shdrt_ServiceStartIdMap *map,
                                    shdrt_Service s) {
  shdrt_ServiceStartIdMap_iter i = shdrt_ServiceStartIdMap_begin(map);

  while (i.ref)
    if (shdrt_Service_equals(&i.ref->second, &s))
      i = shdrt_ServiceStartIdMap_erase_at(map, i);
    else
      shdrt_ServiceStartIdMap_next(&i);
}
