#pragma once

#include "map.h"
#include "start_id_map.h"
#include "service.h"
#include "../intent/intent.h"
#include "bind_flags.h"

typedef struct shdrt_ServiceManager {
	shdrt_ServiceMap created;
	shdrt_ServiceStartIdMap startIds;
} shdrt_ServiceManager;

typedef struct shdrt_ServiceConnection shdrt_ServiceConnection;

shdrt_ServiceManager shdrt_ServiceManager_make();
void shdrt_ServiceManager_drop(shdrt_ServiceManager* man);

void shdrt_ServiceManager_stop_self(shdrt_ServiceManager* man, shdrt_ServiceStartId id);

bool shdrt_ServiceManager_start(shdrt_ServiceManager* man, shdrt_Service s, shdrt_Intent intent);
bool shdrt_ServiceManager_stop(shdrt_ServiceManager* man, shdrt_Service s);

bool shdrt_ServiceManager_bind(shdrt_ServiceManager* man, shdrt_Service s, shdrt_Intent intent, shdrt_ServiceConnection* conn, shdrt_ServiceBindFlags flags);
void shdrt_ServiceManager_unbind(shdrt_ServiceManager* man, shdrt_ServiceConnection* conn);
