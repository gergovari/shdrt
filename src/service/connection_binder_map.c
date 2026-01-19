#include "connection_binder_map.h"

bool shdrt_ServiceConnectionBinderMap_add(shdrt_ServiceConnectionBinderMap* map, shdrt_ServiceConnection* conn, const shdrt_ServiceBinder* binder) {
	return shdrt_ServiceConnectionBinderMap_insert(map, conn, (shdrt_ServiceBinder*)binder).inserted;
}

bool shdrt_ServiceConnectionBinderMap_delete(shdrt_ServiceConnectionBinderMap* map, shdrt_ServiceConnection* conn) {
	return shdrt_ServiceConnectionBinderMap_erase(map, conn);
}

const shdrt_ServiceBinder* shdrt_ServiceConnectionBinderMap_get_binder(shdrt_ServiceConnectionBinderMap* map, shdrt_ServiceConnection* conn) {
	for (c_each_kv(c, binder, shdrt_ServiceConnectionBinderMap, *map)) {
		if (*c == conn) return binder;
	}

	return NULL;
}
