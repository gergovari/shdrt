#include "map.h"

/*shdrt_ServiceContext* shdrt_ServiceMap_add(shdrt_ServiceMap* map, shdrt_Service s, void* user, shdrt_ServiceStopCallback stop) {
	shdrt_ServiceContext* ctx = c_new(shdrt_ServiceContext, {.continuation_mode = 0, .user = user, .stop = stop});
	shdrt_ServiceMap_result res = shdrt_ServiceMap_insert(map, s, ctx);

	return res.inserted ? res.ref->second : NULL;
}*/

bool shdrt_ServiceMap_delete(shdrt_ServiceMap* map, shdrt_Service s) {
	const shdrt_ServiceMap_value* val = shdrt_ServiceMap_get(map, s);

	if (!val) return false;
	c_free(val->second, sizeof(shdrt_ServiceContext));
	shdrt_ServiceMap_erase(map, s);
	return true;
}
