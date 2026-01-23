#pragma once

#include <stc/cstr.h>

#include "../component_id.h"
#include "../intent/intent.h"

#include "binder.h"
#include "context.h"
#include "continuation_mode.h"
#include "start_flags.h"
#include "start_id.h"

typedef struct {
    shdrt_ComponentIdentifier id;
    shdrt_ServiceContinuationMode (*on_start_command)(shdrt_ServiceContext*, shdrt_Intent, shdrt_ServiceStartFlags,
                                                      shdrt_ServiceStartId);

    bool (*on_create)(shdrt_ServiceContext*);
    void (*on_destroy)(shdrt_ServiceContext*);

    shdrt_ServiceBinder* (*on_bind)(shdrt_Intent);
    bool (*on_unbind)(shdrt_Intent);

    shdrt_ServiceBinder* (*on_rebind)(shdrt_Intent);
} shdrt_Service;

int shdrt_Service_cmp(const shdrt_Service* a, const shdrt_Service* b);
bool shdrt_Service_equals(const shdrt_Service* a, const shdrt_Service* b);
