/**
 * @file
 * @brief Defines the @ref shdrt_IntentCategoryFlags type.
 * 
*/

#pragma once

#include "../common.h"

/** @name Intent categories
 * Constants used for intent categories.
 * @{ */

#ifdef DOXYGEN

/**
 * @brief Activity Category: The activity is the initial activity of a task and is listed in the system's application launcher.
 * 
 */
extern const char* SHDRT_INTENT_CATEGORY_FLAG_LAUNCHER;

/**
 * @brief Activity Category: To be used as a test (not part of the normal user experience).
 * 
 */
extern const char* SHDRT_INTENT_CATEGORY_FLAG_TEST;

#else

#define SHDRT_INTENT_CATEGORY_FLAGS_LIST(X)                                                                            \
    X(SHDRT_INTENT_CATEGORY_FLAG_LAUNCHER)                                                                             \
    X(SHDRT_INTENT_CATEGORY_FLAG_TEST)
#define SHDRT_INTENT_CATEGORY_FLAGS_COUNT (0 SHDRT_INTENT_CATEGORY_FLAGS_LIST(COUNT_ITEMS))

#endif // DOXYGEN

/** @} */

#define T shdrt_IntentCategoryBitset, SHDRT_INTENT_CATEGORY_FLAGS_COUNT
#include <stc/cbits.h>
#undef T

typedef enum {

#define GENERATE_ENUM(name) name,
    SHDRT_INTENT_CATEGORY_FLAGS_LIST(GENERATE_ENUM)
#undef GENERATE_ENUM
} shdrt_IntentCategoryFlags;
