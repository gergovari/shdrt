#pragma once

#include <stc/cstr.h>
#include "package/package_id.h"

/**
 * @struct shdrt_ComponentIdentifier
 * @brief Identifies a specific component within a package.
 * 
 * A component identifier consists of a package name and a component name.
 * It uniquely identifies a service or other component in the system.
 */
typedef struct {
    /**
     * @brief The identifier of the package containing the component.
     */
    shdrt_package_identifier_t package;

    /**
     * @brief The name of the component.
     */
    cstr name;
} shdrt_ComponentIdentifier;

/**
 * @brief Creates a new ComponentIdentifier.
 * 
 * @param package The package name (e.g., "com.example.app").
 * @param name The component name (e.g., "MyService").
 * @return A new @ref shdrt_ComponentIdentifier.
 */
shdrt_ComponentIdentifier shdrt_ComponentIdentifier_make(const char* package, const char* name);

/**
 * @brief Creates a deep copy of a ComponentIdentifier.
 * 
 * @param id The identifier to clone.
 * @return A new @ref shdrt_ComponentIdentifier that is a copy of the input.
 */
shdrt_ComponentIdentifier shdrt_ComponentIdentifier_clone(shdrt_ComponentIdentifier id);

/**
 * @brief Frees resources associated with a ComponentIdentifier.
 * 
 * @param id Pointer to the identifier to drop.
 */
void shdrt_ComponentIdentifier_drop(shdrt_ComponentIdentifier* id);

/**
 * @brief Compares two ComponentIdentifiers for ordering.
 * 
 * @param a Pointer to the first identifier.
 * @param b Pointer to the second identifier.
 * @return < 0 if a < b, 0 if a == b, > 0 if a > b.
 */
int shdrt_ComponentIdentifier_cmp(const shdrt_ComponentIdentifier* a, const shdrt_ComponentIdentifier* b);

/**
 * @brief Checks if two ComponentIdentifiers are equal.
 * 
 * @param a Pointer to the first identifier.
 * @param b Pointer to the second identifier.
 * @return true if equal, false otherwise.
 */
int shdrt_ComponentIdentifier_equals(const shdrt_ComponentIdentifier* a, const shdrt_ComponentIdentifier* b);
