#include "manager.h"

#include "context.h"

shdrt_ServiceManager shdrt_ServiceManager_make() {
	return (shdrt_ServiceManager){ .created = { 0 }, .startIds = { 0 } };
}

void shdrt_ServiceManager_drop(shdrt_ServiceManager* man) {
	shdrt_ServiceMap_drop(&man->created);
	shdrt_ServiceStartIdMap_drop(&man->startIds);
}

shdrt_ServiceContext* shdrt_ServiceManager_create(shdrt_ServiceManager* man, shdrt_Service s) {
	shdrt_ServiceContext* ctx;
	
	if (!(ctx = shdrt_ServiceMap_add(&man->created, s, man, shdrt_ServiceManager_stop_self))) return NULL;
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

// TODO flags: NOT_FOREGROUND, ABOVE_CLIENT, WAIVE_PRIORITY, ADJUST_WITH_ACTIVITY, NOT_PERCEPTIBLE, INCLUDE_CAPABILITIES
// TODO: cache binder if on_unbind returns true and if service is started (use intent as key)
// TODO: implement binder funcs
bool shdrt_ServiceManager_bind(shdrt_ServiceManager* man, shdrt_Service s, shdrt_Intent intent, shdrt_ServiceConnection* conn, shdrt_ServiceBindFlags flags) {
	
}
// flag behavs:
// auto create: create the service (but no starting), if not set and service not started return false

void shdrt_ServiceManager_unbind(shdrt_ServiceManager* man, shdrt_ServiceConnection* conn) {

}
