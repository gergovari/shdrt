#pragma once

#include <stc/cstr.h>

typedef cstr shdrt_IntentAction;

#define SHDRT_INTENT_ACTION_LIST \
	X(SHDRT_INTENT_ACTION_MAIN) \
	X(SHDRT_INTENT_ACTION_VIEW) \
	X(SHDRT_INTENT_ACTION_GET_CONTENT) \
	X(SHDRT_INTENT_ACTION_EDIT) \
	X(SHDRT_INTENT_ACTION_DIAL) 

#define X(name) static const char* name = #name;
	SHDRT_INTENT_ACTION_LIST
#undef X

shdrt_IntentAction shdrt_IntentAction_make(const char* name);
int shdrt_IntentAction_cmp(const shdrt_IntentAction* a, const shdrt_IntentAction* b);
