#include "service.h"

#include "../component_id.h"

int shdrt_Service_cmp(const shdrt_Service* a, const shdrt_Service* b) {
	return shdrt_ComponentIdentifier_cmp(&a->id, &b->id);
}
