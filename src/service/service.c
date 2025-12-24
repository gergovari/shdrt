#include "service.h"

int shdrt_Service_cmp(const shdrt_Service* a, const shdrt_Service* b) {
	int c;

	return (c = cstr_cmp(&a->id.package, &b->id.package)) == 0 ? cstr_cmp(&a->id.name, &b->id.name) : c;
}
