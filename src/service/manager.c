#include "manager.h"

#include "context.h"

shdrt_ServiceContext* shdrt_ServiceManager_create(shdrt_ServiceManager* man, shdrt_Service s) {
	shdrt_ServiceContext* ctx;
	
	if (!(ctx = shdrt_ServiceMap_add(&man->created, s, shdrt_ServiceManager_stop_self))) return NULL;
	return ctx;
}

// TODO: implement memory management
void shdrt_ServiceManager_set_continuation_mode(shdrt_Service s, shdrt_ServiceContinuationMode mode) {}

bool shdrt_ServiceManager_start(shdrt_ServiceManager* man, shdrt_Service s, shdrt_Intent intent) {
	shdrt_ServiceContext* ctx;
	shdrt_ServiceStartId id;

	if (!(ctx = shdrt_ServiceManager_create(man, s))) return false;
	
	if (shdrt_ServiceStartIdMap_start(&man->startIds, s, &id)) 
		shdrt_ServiceManager_set_continuation_mode(s, s.on_start_command(ctx, intent, false, id));
		// TODO: implement intent redelivery

	return true;
}

bool shdrt_ServiceManager_stop(shdrt_ServiceManager* man, shdrt_Service s) {
	shdrt_ServiceStartIdMap_forget(&man->startIds, s);
	return shdrt_ServiceMap_delete(&man->created, s);
}

void shdrt_ServiceManager_stop_self(shdrt_ServiceManager* man, shdrt_ServiceStartId id) {
	shdrt_Service s;
	bool res = shdrt_ServiceStartIdMap_get_service(&man->startIds, id, &s);

	if (!res) return;
	if (shdrt_ServiceStartIdMap_stop(&man->startIds, id)) shdrt_ServiceManager_stop(man, s);
}
