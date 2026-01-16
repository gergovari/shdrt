#pragma once

#include <stdbool.h>

#include <stc/cstr.h>

#include "../component_id.h"
#include "category.h"
#include "action.h"
#include "flags.h"

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

int shdrt_Intent_cmp(const shdrt_Intent* a, const shdrt_Intent* b);
bool shdrt_Intent_equals(const shdrt_Intent* a, const shdrt_Intent* b);
