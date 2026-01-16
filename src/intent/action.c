#include "action.h"

shdrt_IntentAction shdrt_IntentAction_make(const char* name) {
	return cstr_from(name);
}

int shdrt_IntentAction_cmp(const shdrt_IntentAction* a, const shdrt_IntentAction* b) {
	return cstr_cmp(a, b);
}
