#pragma once

#include "common.h"

// TODO: implement these
#define SHDRT_CATEGORY_FLAGS_LIST(X) \
	X(SHDRT_CATEGORY_FLAG_LAUNCHER) \
	X(SHDRT_CATEGORY_FLAG_MAIN) \
	X(SHDRT_CATEGORY_FLAG_TEST)
#define SHDRT_CATEGORY_FLAGS_COUNT (0 SHDRT_CATEGORY_FLAGS_LIST(COUNT_ITEMS))

#define T shdrt_CategoryBitset, SHDRT_CATEGORY_FLAGS_COUNT
#include <stc/cbits.h>
#undef T

typedef enum {
#define GENERATE_ENUM(name) name,
	SHDRT_CATEGORY_FLAGS_LIST(GENERATE_ENUM)
#undef GENERATE_ENUM
} shdrt_CategoryFlags;
