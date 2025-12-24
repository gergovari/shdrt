#pragma once

#include "continuation_mode.h"
#include "stop_callback.h"
#include "start_id.h"

typedef struct {
	void* user;
	shdrt_ServiceContinuationMode continuation_mode;
	
	shdrt_ServiceStopCallback stop;
} shdrt_ServiceContext;
