#pragma once

#include "map.h"
#include "start_id_map.h"
#include "service.h"
#include "start_id.h"

typedef struct shdrt_ServiceManager {
	shdrt_ServiceMap created;
	shdrt_ServiceStartIdMap startIds;
} shdrt_ServiceManager;

void shdrt_ServiceManager_stop_self(shdrt_ServiceManager* man, shdrt_ServiceStartId id);
