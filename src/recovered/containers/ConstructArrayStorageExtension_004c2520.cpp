// Original0x004c2520: 144 body bytes plus 0 frozenNOP bytes.
// Initial broad real-constructor/array-element model; source identities remain hypotheses.
#include "shared/array_extension_ordinary_views.hpp"

extern "C" unsigned char array_extension_dispatch_004c2520[];

ArrayStorageExtension_004c2520::ArrayStorageExtension_004c2520(int initial_count, ArrayElementExtension_004c2520* supplied_storage)
    : storage(0), count(initial_count), unknown_0x0c(1), owns_storage(0)
{
    dispatch_table = array_extension_dispatch_004c2520;
    if (initial_count != 0) {
        if (supplied_storage != 0) {
            storage = new (supplied_storage) ArrayElementExtension_004c2520[initial_count];
        } else {
            storage = new ArrayElementExtension_004c2520[initial_count];
            owns_storage = 1;
        }
    }
}
