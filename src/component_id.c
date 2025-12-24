#include "component_id.h"

shdrt_ComponentIdentifier shdrt_ComponentIdentifier_make(const char* package, const char* name) {
	return (shdrt_ComponentIdentifier){.package = cstr_from(package), .name = cstr_from(name)};
}

shdrt_ComponentIdentifier shdrt_ComponentIdentifier_clone(shdrt_ComponentIdentifier id) {
	id.package = cstr_clone(id.package);
	id.name = cstr_clone(id.name);
	return id;
}

void shdrt_ComponentIdentifier_drop(shdrt_ComponentIdentifier* id) {
	cstr_drop(&id->package);
	cstr_drop(&id->name);
}
