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
typedef struct {
    shdrt_ComponentIdentifier id;
    bool explicitId;

    shdrt_IntentAction action;
    bool explicitAction;

    cstr data;
    bool explicitData;

    cstr type;
    bool explicitType;

    shdrt_IntentCategoryFlags category;

    void* extra; // TODO: replace it with smt IPC
    shdrt_IntentFlags flags;
} shdrt_Intent;

/**
 * @brief Compares two @ref shdrt_Intent for equality or ordering.
 * * This function is compatible with standard sort functions.
 *
 * @param a Pointer to the first @ref Intent to compare.
 * @param b Pointer to the second @ref Intent to compare.
 * @return int 
 * - `< 0` if `a` is less than `b`
 * - `0` if `a` and `b` are equal
 * - `> 0` if `a` is greater than `b`
 */
int shdrt_Intent_cmp(const shdrt_Intent* a, const shdrt_Intent* b);

/**
 * @brief Compares two @ref shdrt_Intent for equality.
 * 
 * @param a Pointer to the first @ref Intent.
 * @param b Pointer to the second @ref Intent.
 * @return true 
 * @return false 
 */
bool shdrt_Intent_equals(const shdrt_Intent* a, const shdrt_Intent* b);
