#pragma once

#include <stc/cstr.h>

#include "../component_id.h"

#include "continuation_mode.h"
#include "context.h"
#include "start_id.h"
#include "remote_interface.h"
#include "start_flags.h"

typedef struct shdrt_Intent shdrt_Intent;

typedef struct {
	shdrt_ComponentIdentifier id;
	shdrt_ServiceContinuationMode (*on_start_command)(shdrt_ServiceContext*, shdrt_Intent, shdrt_ServiceStartFlags, shdrt_ServiceStartId);

	bool (*on_create)(shdrt_ServiceContext*);
	bool (*on_destroy)(shdrt_ServiceContext*);

	shdrt_ServiceRemoteInterface* (*on_bind)(shdrt_Intent);
} shdrt_Service;

int shdrt_Service_cmp(const shdrt_Service* a, const shdrt_Service* b);
// TODO: _equals
