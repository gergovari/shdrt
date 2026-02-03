#pragma once

#include <stc/cstr.h>

typedef cstr shdrt_package_identifier_t;

int shdrt_package_identifier_cmp(const shdrt_package_identifier_t* a, const shdrt_package_identifier_t* b);
bool shdrt_package_identifier_equals(const shdrt_package_identifier_t* a, const shdrt_package_identifier_t* b);

shdrt_package_identifier_t shdrt_package_identifier_make(const char* str);