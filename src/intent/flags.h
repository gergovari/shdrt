#pragma once

#include "../common.h"

/** @name Intent Flags
 * Flags controlling how the intent is handled.
 * @{ */

#ifdef DOXYGEN

/* --- Activity Management Flags --- */

/**
 * @brief If set, this activity will become the start of a new task on this history stack.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_NEW_TASK;

/**
 * @brief If set, the activity will not be launched if it is already running at the top of the history stack.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_SINGLE_TOP;

/**
 * @brief If set, and the activity being launched is already running in the current task, then instead of launching a new instance of that activity, all of the other activities on top of it will be closed and this Intent will be delivered to the (now on top) old activity as a new Intent.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_CLEAR_TOP;

/**
 * @brief If set, this flag will cause any existing task that would be associated with this activity to be cleared before the activity is started.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_CLEAR_TASK;

/**
 * @brief If set, the new activity is not kept in the history stack.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_NO_HISTORY;

/**
 * @brief If set, and the task is already running, it represents a "re-launch" of the task and it will be brought to the front.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_REORDER_TO_FRONT;

/**
 * @brief If set, and this intent is being used to launch a new activity from an existing one, the reply target of the existing activity will be transferred to the new activity.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_FORWARD_RESULT;

/**
 * @brief If set, the new activity will not have an animation when being opened.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_NO_ANIMATION;

/**
 * @brief If set, the new activity is not kept in the list of recently launched activities.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS;

/**
 * @brief This flag is used to create a new task and launch an activity into it.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_MULTIPLE_TASK;

/**
 * @brief This flag is used in the split-screen multi-window mode.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_LAUNCH_ADJACENT;

/**
 * @brief This flag is not normally set by application code, but set for you by the system if this activity is being launched from history.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_BROUGHT_TO_FRONT;

/**
 * @brief If set, and this activity is either being started in a new task or bringing to the top an existing task, then it will be launched as the front door of the task.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_RESET_TASK_IF_NEEDED;

/**
 * @brief If set, and this activity is being started in a new task, then it will be launched as the front door of the task.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_PREVIOUS_IS_TOP;

/**
 * @brief If set, this flag will prevent the normal "user hint" protection from being applied to the Intent.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_NO_USER_ACTION;

/**
 * @brief If set, this activity will become the start of a new task on this history stack.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_TASK_ON_HOME;

/**
 * @brief If set, and the activity being launched is already running in the current task, then instead of launching a new instance of that activity, all of the other activities on top of it will be closed and this Intent will be delivered to the (now on top) old activity as a new Intent.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_MATCH_EXTERNAL;

/**
 * @brief If set, the activity will be kept in the list of recently launched activities.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_ACTIVITY_RETAIN_IN_RECENTS;

/* --- Grant / Permission Flags --- */

/**
 * @brief If set, the recipient of this Intent will be granted permission to perform read operations on the URI in the Intent's data.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_GRANT_READ_URI_PERMISSION;

/**
 * @brief If set, the recipient of this Intent will be granted permission to perform write operations on the URI in the Intent's data.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_GRANT_WRITE_URI_PERMISSION;

/**
 * @brief If set, the URI permission grant is persistable.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_GRANT_PERSISTABLE_URI_PERMISSION;

/**
 * @brief If set, the URI permission grant applies to any URI that is a prefix match of the original grant.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_GRANT_PREFIX_URI_PERMISSION;

/* --- Broadcast Receiver Flags --- */

/**
 * @brief If set, the broadcast will be sent to the foreground receiver.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_RECEIVER_FOREGROUND;

/**
 * @brief If set, the broadcast will only be sent to registered receivers.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_RECEIVER_REGISTERED_ONLY;

/**
 * @brief If set, the broadcast will replace any pending broadcast.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_RECEIVER_REPLACE_PENDING;

/**
 * @brief If set, the broadcast will not be aborted.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_RECEIVER_NO_ABORT;

/**
 * @brief If set, the broadcast will be visible to instant apps.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_RECEIVER_VISIBLE_TO_INSTANT_APPS;

/**
 * @brief If set, the broadcast will include stopped packages.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_INCLUDE_STOPPED_PACKAGES;

/**
 * @brief If set, the broadcast will exclude stopped packages.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_EXCLUDE_STOPPED_PACKAGES;

/* --- Debugging & Misc Flags --- */

/**
 * @brief If set, the resolution of this intent will be logged.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_DEBUG_LOG_RESOLUTION;

/**
 * @brief If set, the intent is coming from the background.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_FROM_BACKGROUND;

/**
 * @brief If set, cheek presses will be ignored.
 */
extern const shdrt_IntentFlags SHDRT_INTENT_FLAG_IGNORE_CHEEK_PRESSES;

#else

#define SHDRT_INTENT_FLAGS_LIST(X)                                                                                     \
    /* --- Activity Management Flags --- */                                                                            \
    X(SHDRT_INTENT_FLAG_ACTIVITY_NEW_TASK)                                                                             \
    X(SHDRT_INTENT_FLAG_ACTIVITY_SINGLE_TOP)                                                                           \
    X(SHDRT_INTENT_FLAG_ACTIVITY_CLEAR_TOP)                                                                            \
    X(SHDRT_INTENT_FLAG_ACTIVITY_CLEAR_TASK)                                                                           \
    X(SHDRT_INTENT_FLAG_ACTIVITY_NO_HISTORY)                                                                           \
    X(SHDRT_INTENT_FLAG_ACTIVITY_REORDER_TO_FRONT)                                                                     \
    X(SHDRT_INTENT_FLAG_ACTIVITY_FORWARD_RESULT)                                                                       \
    X(SHDRT_INTENT_FLAG_ACTIVITY_NO_ANIMATION)                                                                         \
    X(SHDRT_INTENT_FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS)                                                                 \
    X(SHDRT_INTENT_FLAG_ACTIVITY_MULTIPLE_TASK)                                                                        \
    X(SHDRT_INTENT_FLAG_ACTIVITY_LAUNCH_ADJACENT)                                                                      \
    X(SHDRT_INTENT_FLAG_ACTIVITY_BROUGHT_TO_FRONT)                                                                     \
    X(SHDRT_INTENT_FLAG_ACTIVITY_RESET_TASK_IF_NEEDED)                                                                 \
    X(SHDRT_INTENT_FLAG_ACTIVITY_PREVIOUS_IS_TOP)                                                                      \
    X(SHDRT_INTENT_FLAG_ACTIVITY_NO_USER_ACTION)                                                                       \
    X(SHDRT_INTENT_FLAG_ACTIVITY_TASK_ON_HOME)                                                                         \
    X(SHDRT_INTENT_FLAG_ACTIVITY_MATCH_EXTERNAL)                                                                       \
    X(SHDRT_INTENT_FLAG_ACTIVITY_RETAIN_IN_RECENTS)                                                                    \
    /* --- Grant / Permission Flags --- */                                                                             \
    X(SHDRT_INTENT_FLAG_GRANT_READ_URI_PERMISSION)                                                                     \
    X(SHDRT_INTENT_FLAG_GRANT_WRITE_URI_PERMISSION)                                                                    \
    X(SHDRT_INTENT_FLAG_GRANT_PERSISTABLE_URI_PERMISSION)                                                              \
    X(SHDRT_INTENT_FLAG_GRANT_PREFIX_URI_PERMISSION)                                                                   \
    /* --- Broadcast Receiver Flags --- */                                                                             \
    X(SHDRT_INTENT_FLAG_RECEIVER_FOREGROUND)                                                                           \
    X(SHDRT_INTENT_FLAG_RECEIVER_REGISTERED_ONLY)                                                                      \
    X(SHDRT_INTENT_FLAG_RECEIVER_REPLACE_PENDING)                                                                      \
    X(SHDRT_INTENT_FLAG_RECEIVER_NO_ABORT)                                                                             \
    X(SHDRT_INTENT_FLAG_RECEIVER_VISIBLE_TO_INSTANT_APPS)                                                              \
    X(SHDRT_INTENT_FLAG_INCLUDE_STOPPED_PACKAGES)                                                                      \
    X(SHDRT_INTENT_FLAG_EXCLUDE_STOPPED_PACKAGES)                                                                      \
    /* --- Debugging & Misc Flags --- */                                                                               \
    X(SHDRT_INTENT_FLAG_DEBUG_LOG_RESOLUTION)                                                                          \
    X(SHDRT_INTENT_FLAG_FROM_BACKGROUND)                                                                               \
    X(SHDRT_INTENT_FLAG_IGNORE_CHEEK_PRESSES)
#define SHDRT_INTENT_FLAGS_COUNT (0 SHDRT_INTENT_FLAGS_LIST(COUNT_ITEMS))

#endif // DOXYGEN

/** @} */

#define T shdrt_IntentBitset, SHDRT_INTENT_FLAGS_COUNT
#include <stc/cbits.h>
#undef T

typedef enum {

#define GENERATE_ENUM(name) name,
    SHDRT_INTENT_FLAGS_LIST(GENERATE_ENUM)
#undef GENERATE_ENUM
} shdrt_IntentFlags;
