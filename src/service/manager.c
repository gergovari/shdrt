#include "manager.h"

void shdrt_ServiceManager_stop_self(shdrt_ServiceManager* man, shdrt_ServiceStartId id) {
	shdrt_Service s;
	bool res = shdrt_ServiceStartIdMap_get_service(&man->startIds, id, &s);

	if (!res) return;
	//if (shdrt_ServiceStartIdMap_stop(man->startIds, id)) shdrt_ServiceManager_stop_service(man, s);
}
