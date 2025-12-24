#pragma once

#include "../common.h"

#define SHDRT_SERVICE_START_FLAGS_LIST(X) \
	X(SHDRT_SERVICE_START_FLAG_REDELIVERY) \
	X(SHDRT_SERVICE_START_FLAG_RETRY) 
#define SHDRT_SERVICE_START_FLAGS_COUNT (0 SHDRT_SERVICE_START_FLAGS_LIST(COUNT_ITEMS))

#define T shdrt_ServiceStartBitset, SHDRT_SERVICE_START_FLAGS_COUNT
#include <stc/cbits.h>
#undef T

typedef enum {
#define GENERATE_ENUM(name) name,
	SHDRT_SERVICE_START_FLAGS_LIST(GENERATE_ENUM)
#undef GENERATE_ENUM
} shdrt_ServiceStartFlags;
