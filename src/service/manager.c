#include "manager.h"

#include "bind_flags.h"
#include "context.h"
#include "context_map.h"

// TODO: error handling (like if add returns false and such)

bool shdrt_ServiceManager_is_used(shdrt_ServiceManager* man, shdrt_Service s) {
	return shdrt_ServiceContextMap_is_created(&man->created, s) || shdrt_ServiceConnectionMap_is_bound(&man->conns, s);
}

shdrt_ServiceManager shdrt_ServiceManager_make() {
	return (shdrt_ServiceManager){ .created = { 0 }, .startIds = { 0 }, .conns = { 0 }, .binders = { 0 }, .intents = { 0 }, .connBinders = { 0 } };
}

void shdrt_ServiceManager_drop(shdrt_ServiceManager* man) {
	shdrt_ServiceContextMap_drop(&man->created);
	shdrt_ServiceStartIdMap_drop(&man->startIds);
}

shdrt_ServiceContext* shdrt_ServiceManager_create(shdrt_ServiceManager* man, shdrt_Service s) {
	shdrt_ServiceContext* ctx;
	
	if (!(ctx = shdrt_ServiceContextMap_get(&man->created, s)->second)) 
		ctx = shdrt_ServiceContextMap_create(&man->created, s, man, shdrt_ServiceManager_stop_self);
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
	return shdrt_ServiceContextMap_destroy(&man->created, s);
}

void shdrt_ServiceManager_stop_self(shdrt_ServiceManager* man, shdrt_ServiceStartId id) {
	shdrt_Service s;
	bool res = shdrt_ServiceStartIdMap_get_service(&man->startIds, id, &s);

	if (!res) return;
	if (shdrt_ServiceStartIdMap_stop(&man->startIds, id)) shdrt_ServiceManager_stop(man, s);
}

// TODO flags: NOT_FOREGROUND, ABOVE_CLIENT, WAIVE_PRIORITY, ADJUST_WITH_ACTIVITY, NOT_PERCEPTIBLE, INCLUDE_CAPABILITIES
bool shdrt_ServiceManager_bind(shdrt_ServiceManager* man, shdrt_Service s, shdrt_Intent intent, shdrt_ServiceConnection* conn, shdrt_ServiceBindBitset flags) {
	const shdrt_ServiceBinder* binder;
	bool ret;

	if (shdrt_ServiceBindBitset_is_set(flags, SHDRT_SERVICE_BIND_FLAG_AUTO_CREATE)) shdrt_ServiceManager_create(man, s);
	if (!shdrt_ServiceManager_is_used(man, s)) return false;

	if (!shdrt_ServiceConnectionMap_add(&man->conns, s, conn)) return false;

	binder = shdrt_ServiceBinderMap_get_binder(&man->binders, s, intent);
	conn->on_service_connected(s.id, binder == NULL ? s.on_bind(intent) : binder);

	ret = shdrt_ServiceConnectionIntentMap_add(&man->intents, conn, intent);
	ret = shdrt_ServiceConnectionBinderMap_add(&man->connBinders, conn, binder);

	return ret;
}

void shdrt_ServiceManager_unbind(shdrt_ServiceManager* man, shdrt_ServiceConnection* conn) {
	bool used;
	shdrt_Service s;
	shdrt_Intent intent;
	const shdrt_ServiceBinder* binder = shdrt_ServiceConnectionBinderMap_get_binder(&man->connBinders, conn);
	
	if (!binder) return;
	if (!shdrt_ServiceConnectionMap_get_service(&man->conns, conn, &s)) return;
	if (!shdrt_ServiceConnectionIntentMap_get_intent(&man->intents, conn, &intent)) return;
	
	shdrt_ServiceConnectionMap_delete(&man->conns, conn);
	shdrt_ServiceConnectionIntentMap_delete(&man->intents, conn);
	shdrt_ServiceConnectionBinderMap_delete(&man->connBinders, conn);
	
	used = shdrt_ServiceManager_is_used(man, s);
	if (s.on_unbind(intent) && used) shdrt_ServiceBinderMap_add(&man->binders, s, intent, binder);
	if (!used) { 
		shdrt_ServiceBinderMap_delete(&man->binders, s);
	}
}
