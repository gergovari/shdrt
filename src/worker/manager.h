#pragma once

#include <stdbool.h>

#include "../component_id.h"

typedef struct shdrt_worker_manager {
} shdrt_worker_manager_t;

bool shdrt_worker_manager_start_service(shdrt_worker_manager_t* this, shdrt_ComponentIdentifier id);