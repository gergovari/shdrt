#include "component_id.h"

shdrt_ComponentIdentifier shdrt_ComponentIdentifier_make(const char *package,
                                                         const char *name) {
  return (shdrt_ComponentIdentifier){.package = cstr_from(package),
                                     .name = cstr_from(name)};
}

shdrt_ComponentIdentifier
shdrt_ComponentIdentifier_clone(shdrt_ComponentIdentifier id) {
  id.package = cstr_clone(id.package);
  id.name = cstr_clone(id.name);
  return id;
}

void shdrt_ComponentIdentifier_drop(shdrt_ComponentIdentifier *id) {
  cstr_drop(&id->package);
  cstr_drop(&id->name);
}

int shdrt_ComponentIdentifier_cmp(const shdrt_ComponentIdentifier *a,
                                  const shdrt_ComponentIdentifier *b) {
  int c;

  return (c = cstr_cmp(&a->package, &b->package)) == 0
             ? cstr_cmp(&a->name, &b->name)
             : c;
}

int shdrt_ComponentIdentifier_equals(const shdrt_ComponentIdentifier *a,
                                     const shdrt_ComponentIdentifier *b) {
  return shdrt_ComponentIdentifier_cmp(a, b) == 0;
}
