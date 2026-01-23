#include "bind_flags.h"

bool shdrt_ServiceBindBitset_is_set(shdrt_ServiceBindBitset flags,
                                    shdrt_ServiceBindFlags at) {
  return shdrt_ServiceBindBitset_at(&flags, at);
}