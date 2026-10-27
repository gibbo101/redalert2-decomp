// Original region: 0x00653730 (93 body bytes, 3 independently frozen NOP bytes).
// Exact target SHA256: e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f.
// Purpose: initialize an inferred four-byte-element storage wrapper.
// Class/API identity and the three unknown field purposes remain unresolved.

extern "C" void* __cdecl allocate_storage_00653730(unsigned int byte_count);
extern "C" unsigned char base_dispatch_00653730[];
extern "C" unsigned char derived_dispatch_00653730[];

class WordStorage_00653730 {
    unsigned char* dispatch_table;
    unsigned int* storage;
    unsigned int capacity;
    unsigned char unknown_0x0c;
    unsigned char owns_storage;
    // Bytes 0x0e..0x0f are alignment padding and are not written.
    unsigned int unknown_0x10;
    unsigned int unknown_0x14;

public:
    WordStorage_00653730* initialize(unsigned int requested_capacity,
                                unsigned int* supplied_storage);
};

typedef char WordStorage_00653730_size_check[(sizeof(WordStorage_00653730) == 24) ? 1 : -1];

WordStorage_00653730* WordStorage_00653730::initialize(
    unsigned int requested_capacity,
    unsigned int* supplied_storage)
{
    storage = 0;
    capacity = requested_capacity;
    unknown_0x0c = 1;
    owns_storage = 0;
    dispatch_table = base_dispatch_00653730;

    // A zero capacity ignores even a nonnull supplied pointer.
    if (requested_capacity != 0) {
        if (supplied_storage != 0) {
            storage = supplied_storage;
        } else {
            // Preserve 32-bit wrapping and ownership even on a null result.
            storage = (unsigned int*)allocate_storage_00653730(requested_capacity << 2);
            owns_storage = 1;
        }
    }

    dispatch_table = derived_dispatch_00653730;
    unknown_0x14 = 10;
    unknown_0x10 = 0;
    return this;
}
