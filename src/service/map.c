#include "map.h"

shdrt_ServiceContext* shdrt_ServiceMap_add(shdrt_ServiceMap* map, shdrt_Service s, shdrt_ServiceStopCallback stop) {
	shdrt_ServiceContext* ctx = c_new(shdrt_ServiceContext, {.continuation_mode = 0, .stop = stop});
	shdrt_ServiceMap_result res = shdrt_ServiceMap_insert(map, s, ctx);
	
	if (!res.inserted) return NULL;
	return s.on_create(ctx) ? ctx : NULL;
}

bool shdrt_ServiceMap_delete(shdrt_ServiceMap* map, shdrt_Service s) {
	const shdrt_ServiceMap_value* val = shdrt_ServiceMap_get(map, s);
	shdrt_ServiceContext* ctx;

	if (!val) return false;
	ctx = val->second;
	
	s.on_destroy(ctx);
	shdrt_ServiceMap_erase(map, s);
	c_free(ctx, sizeof(shdrt_ServiceContext));
	return true;
}
