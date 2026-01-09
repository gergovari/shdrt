#pragma once

#include "map.h"
#include "start_id_map.h"
#include "service.h"
#include "../intent.h"

typedef struct shdrt_ServiceManager {
	shdrt_ServiceMap created;
	shdrt_ServiceStartIdMap startIds;
} shdrt_ServiceManager;

void shdrt_ServiceManager_stop_self(shdrt_ServiceManager* man, shdrt_ServiceStartId id);

bool shdrt_ServiceManager_start(shdrt_ServiceManager* man, shdrt_Service s, shdrt_Intent intent);
bool shdrt_ServiceManager_stop(shdrt_ServiceManager* man, shdrt_Service s);

// TODO: bound services
