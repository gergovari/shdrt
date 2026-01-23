#pragma once

#include "start_id.h"

typedef struct shdrt_ServiceManager shdrt_ServiceManager;

typedef void (*shdrt_ServiceStopCallback)(shdrt_ServiceManager *,
                                          shdrt_ServiceStartId);
