/**
 * @file
 * @brief Defines the @ref shdrt_IntentAction type and standard action constants.
 *
 * This header provides the type definition for Intent Actions, which represent
 * the general operation to be performed (e.g., viewing or editing data).
 * It includes a registry of standard action constants used throughout the system.
 *
 */

#pragma once

#include <stc/cstr.h>

/**
 * @typedef shdrt_IntentAction
 * @brief Represents a general operation to be performed by an @ref Intent.
 *
 * An action is essentially a string identifier (e.g., "SHDRT_INTENT_ACTION_MAIN").
 * Use the provided static constants (e.g., @ref SHDRT_INTENT_ACTION_VIEW) 
 * whenever possible to ensure type safety and consistency.
 */
typedef cstr shdrt_IntentAction;

/** @name Intent Actions
 * Constants used for intent actions.
 * @{ */

#ifdef DOXYGEN

/** 
 * @brief Activity Action: Start as a main entry point.
 * does not expect to receive data.
 */
const char* SHDRT_INTENT_ACTION_MAIN;

/** 
 * @brief Activity Action: Display the data to the user.
 * This is the most common action performed on data.
 */
const char* SHDRT_INTENT_ACTION_VIEW;

/** 
 * @brief Activity Action: Allow the user to select a particular kind of data and return it.
 */
const char* SHDRT_INTENT_ACTION_GET_CONTENT;

/** 
 * @brief Activity Action: Provide explicit editable access to the given data.
 */
const char* SHDRT_INTENT_ACTION_EDIT;

/** 
 * @brief Activity Action: Dial a number as specified by the data.
 * This shows a UI with the number being dialed, allowing the user to explicitly initiate the call.
 */
const char* SHDRT_INTENT_ACTION_DIAL;

#else

#define SHDRT_INTENT_ACTION_LIST                                                                                       \
    X(SHDRT_INTENT_ACTION_MAIN)                                                                                        \
    X(SHDRT_INTENT_ACTION_VIEW)                                                                                        \
    X(SHDRT_INTENT_ACTION_GET_CONTENT)                                                                                 \
    X(SHDRT_INTENT_ACTION_EDIT)                                                                                        \
    X(SHDRT_INTENT_ACTION_DIAL)

#define X(name) static const char* name = #name;
SHDRT_INTENT_ACTION_LIST
#undef X

#endif // DOXYGEN

/** @} */

/**
 * @brief Creates a new @ref shdrt_IntentAction from a raw string.
 *
 * @param name The raw string identifier for the action (e.g., "COM_ACTION_CUSTOM").
 * The function may copy this string depending on implementation.
 * @return A new @ref shdrt_IntentAction object.
 */
shdrt_IntentAction shdrt_IntentAction_make(const char* name);

/**
 * @brief Compares two @ref shdrt_IntentAction for equality or ordering.
 * * This function is compatible with standard sort functions.
 *
 * @param a Pointer to the first action to compare.
 * @param b Pointer to the second action to compare.
 * @return int 
 * - `< 0` if `a` is less than `b`
 * - `0` if `a` and `b` are equal
 * - `> 0` if `a` is greater than `b`
 */
int shdrt_IntentAction_cmp(const shdrt_IntentAction* a, const shdrt_IntentAction* b);