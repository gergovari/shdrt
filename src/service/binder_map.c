#include "binder_map.h"

// TODO

/*bool shdrt_ServiceConnectionMap_add(shdrt_ServiceConnectionMap* map, shdrt_Service s, shdrt_ServiceConnection* conn) {
	shdrt_ServiceConnectionSet set = shdrt_ServiceConnectionSet_with_capacity(1);
	shdrt_ServiceConnectionMap_value* val = shdrt_ServiceConnectionMap_get_mut(map, s);
	
	shdrt_ServiceConnectionSet_push(&set, conn);
	return val ? shdrt_ServiceConnectionSet_insert(&val->second, conn).inserted : shdrt_ServiceConnectionMap_insert(map, s, set).inserted;
}

bool shdrt_ServiceConnectionMap_delete(shdrt_ServiceConnectionMap* map, shdrt_ServiceConnection* conn) {
	for (c_each_kv(s, set, shdrt_ServiceConnectionMap, *map)) {
		if (shdrt_ServiceConnectionSet_erase(set, conn)) {
			if (shdrt_ServiceConnectionSet_size(set) == 0) shdrt_ServiceConnectionMap_erase(map, *s);
			return true;
		}
	}

	return false;
}*/
