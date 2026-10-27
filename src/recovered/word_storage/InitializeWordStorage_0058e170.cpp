// Original region: 0x0058e170 (93 body bytes, 3 independently frozen NOP bytes).
// Exact target SHA256: e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f.
// Purpose: initialize an inferred four-byte-element storage wrapper.
// Class/API identity and the three unknown field purposes remain unresolved.

extern "C" void* __cdecl allocate_storage_0058e170(unsigned int byte_count);
extern "C" unsigned char base_dispatch_0058e170[];
extern "C" unsigned char derived_dispatch_0058e170[];

#include "shared/word_storage_layout.hpp"

WordStorage_0058e170* WordStorage_0058e170::initialize(
    unsigned int requested_capacity,
    unsigned int* supplied_storage)
{
    storage = 0;
    capacity = requested_capacity;
    unknown_0x0c = 1;
    owns_storage = 0;
    dispatch_table = base_dispatch_0058e170;

    // A zero capacity ignores even a nonnull supplied pointer.
    if (requested_capacity != 0) {
        if (supplied_storage != 0) {
            storage = supplied_storage;
        } else {
            // Preserve 32-bit wrapping and ownership even on a null result.
            storage = (unsigned int*)allocate_storage_0058e170(requested_capacity << 2);
            owns_storage = 1;
        }
    }

    dispatch_table = derived_dispatch_0058e170;
    unknown_0x14 = 10;
    unknown_0x10 = 0;
    return this;
}
