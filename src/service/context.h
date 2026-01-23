#pragma once

#include "continuation_mode.h"
#include "start_id.h"
#include "stop_callback.h"

typedef struct shdrt_ServiceManager shdrt_ServiceManager;

typedef struct {
  void *user;
  shdrt_ServiceContinuationMode continuation_mode;

  shdrt_ServiceStopCallback stop;

  shdrt_ServiceManager *man;
} shdrt_ServiceContext;
