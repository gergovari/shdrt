/** @file */
#pragma once

#include <stdbool.h>

#include <stc/cstr.h>

#include "../component_id.h"
#include "action.h"
#include "category.h"
#include "flags.h"

/**
 * @brief An intent is an abstract description of an operation to be performed.
 * 
 */
/**
 * @struct shdrt_Intent
 * @brief An intent is an abstract description of an operation to be performed.
 * 
 * Intents are used to request an action from another component in the system.
 * They carry information about what action to perform, what data to act upon,
 * and additional categories or flags to refine the request.
 */
typedef struct {
    /**
     * @brief The target component identifier for this intent.
     * 
     * If `explicitId` is true, this field specifies the exact component that should handle the intent.
     */
    shdrt_ComponentIdentifier id;
    
    /**
     * @brief Flag indicating if the target component ID is explicitly set.
     */
    bool explicitId;

    /**
     * @brief The action to be performed (e.g., ACTION_VIEW, ACTION_SEND).
     */
    shdrt_IntentAction action;
    
    /**
     * @brief Flag indicating if the action is efficiently set.
     */
    bool explicitAction;

    /**
     * @brief The data to operate on, typically a URI.
     */
    cstr data;
    
    /**
     * @brief Flag indicating if the data field is set.
     */
    bool explicitData;

    /**
     * @brief The MIME type of the data.
     */
    cstr type;
    
    /**
     * @brief Flag indicating if the type field is set.
     */
    bool explicitType;

    /**
     * @brief Categories associated with the intent (e.g., CATEGORY_LAUNCHER).
     */
    shdrt_IntentCategoryFlags category;

    /**
     * @brief Extra data associated with the intent.
     * 
     * @warning This field is currently a raw pointer and its usage is subject to change.
     * Future implementations may replace this with a safer IPC mechanism.
     */
    void* extra; 
    
    /**
     * @brief Flags controlling how the intent is handled.
     */
    shdrt_IntentFlags flags;
} shdrt_Intent;

/**
 * @brief Compares two @ref shdrt_Intent objects for equality or ordering.
 * 
 * This function defines a total ordering for intents, which is useful for
 * storing them in sorted collections or maps.
 *
 * @param a Pointer to the first @ref shdrt_Intent to compare.
 * @param b Pointer to the second @ref shdrt_Intent to compare.
 * @return int 
 * - `< 0` if `a` is strictly less than `b`
 * - `0` if `a` and `b` are equal
 * - `> 0` if `a` is strictly greater than `b`
 */
int shdrt_Intent_cmp(const shdrt_Intent* a, const shdrt_Intent* b);

/**
 * @brief Checks if two @ref shdrt_Intent objects are equal.
 * 
 * Equality is determined by comparing all fields of the intent.
 * 
 * @param a Pointer to the first @ref shdrt_Intent.
 * @param b Pointer to the second @ref shdrt_Intent.
 * @return true if the intents are equal, false otherwise.
 */
bool shdrt_Intent_equals(const shdrt_Intent* a, const shdrt_Intent* b);
