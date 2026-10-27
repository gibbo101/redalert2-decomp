// Original0x0042ce60: 117 body bytes plus 11 frozenNOP bytes.
// Initial broad real-constructor/array-element model; source identities remain hypotheses.
#include "shared/array_extension_ordinary_views.hpp"

extern "C" unsigned char array_extension_dispatch_0042ce60[];

ArrayStorageExtension_0042ce60::ArrayStorageExtension_0042ce60(int initial_count, ArrayElementExtension_0042ce60* supplied_storage)
    : ArrayStorageBaseExtension_0042ce60(initial_count, supplied_storage)
{
    dispatch_table = array_extension_dispatch_0042ce60;
    unknown_0x14 = 10;
    unknown_0x10 = 0;
}
