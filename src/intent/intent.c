#include "intent.h"

#include <stc/cstr.h>

#include "../component_id.h"

int shdrt_Intent_cmp(const shdrt_Intent* a, const shdrt_Intent* b) {
	bool id = a->explicitId && b->explicitId ? shdrt_ComponentIdentifier_equals(&a->id, &b->id) : a->explicitId == b->explicitId;
	bool action = a->explicitAction && b->explicitAction ? cstr_cmp(&a->action, &b->action) == 0 : a->explicitAction == b->explicitAction;
	bool data = a->explicitData && b->explicitData ? cstr_cmp(&a->data, &b->data) == 0 : a->explicitData == b->explicitData;
	bool type = a->explicitType && b->explicitType ? cstr_cmp(&a->type, &b->type) == 0 : a->explicitType == b->explicitType;
	bool category = a->category == b->category;

	if (id && action && data && type && category) return 0;

	if (a->explicitId == b->explicitId && a->explicitId) return shdrt_ComponentIdentifier_cmp(&a->id, &b->id);
	if (a->explicitAction == b->explicitAction && a->explicitAction) return cstr_cmp(&a->action, &b->action);
	
	return a->explicitId ? 1 : -1;
}

bool shdrt_Intent_equals(const shdrt_Intent* a, const shdrt_Intent* b) {
	return shdrt_Intent_cmp(a, b) == 0;
}
