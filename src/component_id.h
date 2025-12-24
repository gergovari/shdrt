#pragma once

#include <stc/cstr.h>

typedef struct {
	cstr package;
	cstr name;
} shdrt_ComponentIdentifier;

shdrt_ComponentIdentifier shdrt_ComponentIdentifier_make(const char* package, const char* name);
shdrt_ComponentIdentifier shdrt_ComponentIdentifier_clone(shdrt_ComponentIdentifier id);
void shdrt_ComponentIdentifier_drop(shdrt_ComponentIdentifier* id);
