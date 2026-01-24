#pragma once

#include <stdbool.h>
#include "start_id.h"

typedef struct shdrt_ServiceManager shdrt_ServiceManager;

typedef bool (*shdrt_ServiceStopCallback)(shdrt_ServiceManager*, shdrt_ServiceStartId);
