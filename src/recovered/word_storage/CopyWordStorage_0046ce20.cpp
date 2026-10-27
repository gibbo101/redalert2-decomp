// Original 0x0046ce20: 136 body bytes and 8 independently frozen NOP bytes.
// Target SHA256 e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f.
// Purpose: initialize a 24-byte word-storage wrapper by copying another wrapper.
// Concrete game class, original method name, and fields 0x0c/0x10/0x14 are unknown.

#include "shared/word_storage_layout.hpp"

extern "C" void* __cdecl allocate_words_0046ce20(unsigned int byte_count);
extern "C" unsigned char base_dispatch_0046ce20[];
extern "C" unsigned char derived_dispatch_0046ce20[];
// Actual original static base-table slot; ECX receiver and RET0 callee.
// Fastcall-compatible declaration preserves observed ABI, not an original API name.
extern "C" void (__fastcall *clear_storage_slot_0046ce20)(WordStorage_0046d1f0*);

WordStorage_0046d1f0* WordStorage_0046d1f0::CopyWordStorage_0046ce20(
    const WordStorage_0046d1f0& source)
{
    // These writes precede the self-copy test; self-copy deliberately loses the
    // prior pointer/count without freeing it, while retaining unknown tail fields.
    storage = 0;
    capacity = 0;
    unknown_0x0c = 1;
    owns_storage = 0;
    dispatch_table = base_dispatch_0046ce20;
    if (this != &source) {
        clear_storage_slot_0046ce20(this);
        capacity = source.capacity;
        if (capacity != 0) {
            // Allocation uses the raw count bits with wrapping 32-bit scaling.
            storage = (unsigned int*)allocate_words_0046ce20((unsigned int)capacity << 2);
            if (storage != 0) {
                owns_storage = 1;
                // The signed loop and live pointer/count reloads preserve aliases.
                for (int index = 0; index < capacity; ++index) {
                    storage[index] = source.storage[index];
                }
            }
        } else {
            storage = 0;
            owns_storage = 0;
        }
    }
    unknown_0x10 = source.unknown_0x10;
    unknown_0x14 = source.unknown_0x14;
    dispatch_table = derived_dispatch_0046ce20;
    return this;
}
