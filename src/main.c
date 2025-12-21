#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <stc/cstr.h>
#include <stc/cbits.h>
#include <stc/common.h>

#define COUNT_ITEMS(name) +1

typedef struct {
	cstr package;
	cstr name;
} shdrt_ComponentIdentifier;
shdrt_ComponentIdentifier shdrt_ComponentIdentifier_make(const char* package, const char* name) {
	return (shdrt_ComponentIdentifier){.package = cstr_from(package), .name = cstr_from(name)};
}
shdrt_ComponentIdentifier shdrt_ComponentIdentifier_clone(shdrt_ComponentIdentifier id) {
	id.package = cstr_clone(id.package);
	id.name = cstr_clone(id.name);
	return id;
}
void shdrt_ComponentIdentifier_drop(shdrt_ComponentIdentifier* id) {
	cstr_drop(&id->package);
	cstr_drop(&id->name);
}

typedef enum {
	shdrt_SERVICE_START_STICKY,
	shdrt_SERVICE_START_NOT_STICKY,
	shdrt_SERVICE_START_REDELIVER_INTENT
} shdrt_ServiceContinuationMode;
typedef int64_t shdrt_ServiceStartId;


#define SHDRT_SERVICE_START_FLAGS_LIST(X) \
	X(shdrt_SERVICE_START_FLAG_REDELIVERY) \
	X(shdrt_SERVICE_START_FLAG_RETRY) 
#define SHDRT_SERVICE_START_FLAGS_COUNT (0 SHDRT_SERVICE_START_FLAGS_LIST(COUNT_ITEMS))
#define T shdrt_ServiceStartBitset, SHDRT_SERVICE_START_FLAGS_COUNT
#include <stc/cbits.h>
#undef T
typedef enum {
#define GENERATE_ENUM(name) name,
	SHDRT_SERVICE_START_FLAGS_LIST(GENERATE_ENUM)
#undef GENERATE_ENUM
} shdrt_ServiceStartFlags;

typedef struct {
	void* user;
	shdrt_ServiceContinuationMode continuation_mode;

	void (*stop)(shdrt_ServiceStartId);
} shdrt_ServiceContext;

typedef struct {
	int dummy; // TODO
} shdrt_Intent;

typedef void shdrt_RemoteInterface;

typedef struct {
	shdrt_ComponentIdentifier id;
	shdrt_ServiceContinuationMode (*on_start_command)(shdrt_ServiceContext*, shdrt_Intent, shdrt_ServiceStartFlags, shdrt_ServiceStartId);
	
	bool (*on_create)(shdrt_ServiceContext);
	bool (*on_destroy)(shdrt_ServiceContext);

	shdrt_RemoteInterface* (*on_bind)(shdrt_Intent);
} shdrt_Service;
static int shdrt_Service_cmp(const shdrt_Service* a, const shdrt_Service* b) {
	int c;

	return (c = cstr_cmp(&a->id.package, &b->id.package)) == 0 ? cstr_cmp(&a->id.name, &b->id.name) : c;
}

#define T shdrt_ServiceMap, shdrt_Service, shdrt_ServiceContext*
#define i_cmp shdrt_Service_cmp
#include <stc/sortedmap.h>
#undef T
typedef void(*shdrt_ServiceStopCallback)(shdrt_ServiceStartId);
shdrt_ServiceContext* shdrt_ServiceMap_add(shdrt_ServiceMap* map, shdrt_Service s, shdrt_ServiceStopCallback stop) {
	shdrt_ServiceContext* ctx = c_new(shdrt_ServiceContext, {.user = NULL, .continuation_mode = 0, .stop = stop});
	shdrt_ServiceMap_result res = shdrt_ServiceMap_insert(map, s, ctx);

	return res.inserted ? res.ref->second : NULL;
}
bool shdrt_ServiceMap_delete(shdrt_ServiceMap* map, shdrt_Service s) {
	const shdrt_ServiceMap_value* val = shdrt_ServiceMap_get(map, s);

	if (!val) return false;
	c_free(val->second, sizeof(shdrt_ServiceContext));
	shdrt_ServiceMap_erase(map, s);
	return true;
}

struct ServiceManager {
	shdrt_ServiceMap created;
	shdrt_StartIdMap startIds;
}

int main(int argc, char *argv[]) {
	return EXIT_SUCCESS;
}
