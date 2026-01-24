#pragma once

#include "context_map.h"
#include "start_id_map.h"

#include "../intent/intent.h"
#include "service.h"

/*#include "bind_flags.h"
#include "binder_map.h"
#include "connection_binder_map.h"
#include "connection_intent_map.h"
#include "connection_map.h"*/

typedef struct shdrt_ServiceManager {
    shdrt_ServiceContextMap created;
    shdrt_ServiceStartIdMap startIds;

    /*shdrt_ServiceConnectionMap conns;
  shdrt_ServiceBinderMap binders;
  shdrt_ServiceConnectionIntentMap intents;
  shdrt_ServiceConnectionBinderMap connBinders;*/
} shdrt_ServiceManager;

typedef struct shdrt_ServiceConnection shdrt_ServiceConnection;

shdrt_ServiceManager shdrt_ServiceManager_make();
void shdrt_ServiceManager_drop(shdrt_ServiceManager* man);

bool shdrt_ServiceManager_stop_self(shdrt_ServiceManager* man, shdrt_ServiceStartId id);

bool shdrt_ServiceManager_start(shdrt_ServiceManager* man, shdrt_Service s, shdrt_Intent intent);
bool shdrt_ServiceManager_stop(shdrt_ServiceManager* man, shdrt_Service s);

/*bool shdrt_ServiceManager_bind(shdrt_ServiceManager *man, shdrt_Service s,
                               shdrt_Intent intent,
                               shdrt_ServiceConnection *conn,
                               shdrt_ServiceBindBitset flags);
void shdrt_ServiceManager_unbind(shdrt_ServiceManager *man,
                                 shdrt_ServiceConnection *conn);*/
