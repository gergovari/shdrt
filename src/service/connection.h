#pragma once

#include "../component_id.h"
#include "binder.h"

typedef struct shdrt_ServiceConnection {
	void (*on_binding_died)(shdrt_ComponentIdentifier id);
	void (*on_null_binding)(shdrt_ComponentIdentifier id);
	void (*on_service_disconnected)(shdrt_ComponentIdentifier id);

	void (*on_service_connected)(shdrt_ComponentIdentifier id, shdrt_ServiceBinder* binder);
} shdrt_ServiceConnection;
