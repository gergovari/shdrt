#include "binder_map.h"

bool shdrt_ServiceBinderMap_add(shdrt_ServiceBinderMap* map, shdrt_Service s, shdrt_Intent intent, shdrt_ServiceBinder* binder) {
	shdrt_ServiceBinderMap_iter it = shdrt_ServiceBinderMap_find(map, s);

	if (it.ref == NULL) {
		shdrt_ServiceIntentBinderMap inner = shdrt_ServiceIntentBinderMap_init();
		shdrt_ServiceBinderMap_result res = shdrt_ServiceBinderMap_insert(map, s, inner);
		
		if (!res.inserted) return false;

		it.ref = res.ref;
	}

	shdrt_ServiceIntentBinderMap_result res = shdrt_ServiceIntentBinderMap_insert_or_assign(&it.ref->second, intent, binder);

	return res.inserted;
}

bool shdrt_ServiceBinderMap_delete(shdrt_ServiceBinderMap* map, shdrt_Service s) {
	return shdrt_ServiceBinderMap_erase(map, s);
}
