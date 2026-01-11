#pragma once

#include <stdbool.h>

#include <stc/cstr.h>

#include "component_id.h"
#include "category_flags.h"
#include "intent_flags.h"

typedef struct {
	shdrt_ComponentIdentifier id;
	bool explicitId;

	cstr action;
	bool explicitAction;

	cstr data;
	bool explicitData;

	cstr type;
	bool explicitType;

	shdrt_CategoryFlags category;

	void* extra;
	shdrt_IntentFlags flags;
} shdrt_Intent;

int shdrt_Intent_cmp(const shdrt_Intent* a, const shdrt_Intent* b);
bool shdrt_Intent_equals(const shdrt_Intent* a, const shdrt_Intent* b);
