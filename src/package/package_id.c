#include "package_id.h"
#include "stc/cstr.h"

int
shdrt_package_identifier_cmp(const shdrt_package_identifier_t* a, const shdrt_package_identifier_t* b) {
    return cstr_cmp(a, b);
}

bool
shdrt_package_identifier_equals(const shdrt_package_identifier_t* a, const shdrt_package_identifier_t* b) {
    return shdrt_package_identifier_cmp(a, b) == 0;
}

shdrt_package_identifier_t
shdrt_package_identifier_make(const char* str) {
    return cstr_from(str);
}