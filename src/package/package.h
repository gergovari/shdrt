#pragma once

#include "../component_id.h"
#include "../service/service.h" // IWYU pragma: keep
#include "package_id.h"

#define T shdrt_service_list, shdrt_Service
#include <stc/list.h>
#undef T

/**
 * @struct shdrt_package
 * @brief Represents a loaded package containing services.
 * 
 * A package is a collection of components, currently primarily services.
 */
typedef struct shdrt_package {
    /**
     * @brief List of services contained in this package.
     */
    shdrt_service_list services;
} shdrt_package_t;

/**
 * @brief Loads a package by its identifier.
 * 
 * @param id The unique identifier of the package to load.
 * @return A pointer to the loaded @ref shdrt_package_t, or NULL if loading failed.
 */
shdrt_package_t* shdrt_package_load(shdrt_package_identifier_t id);

/**
 * @brief Unloads a package and frees its resources.
 * 
 * @param this Pointer to the package to unload.
 */
void shdrt_package_unload(shdrt_package_t* this);

/**
 * @brief Retrieves a service definition from a loaded package.
 * 
 * @param this Pointer to the package.
 * @param id The component identifier of the service to find.
 * @param s Pointer to a @ref shdrt_Service struct where the result will be copied.
 * @return true if the service was found, false otherwise.
 */
bool shdrt_package_get_service(shdrt_package_t* this, shdrt_ComponentIdentifier id, shdrt_Service* s);