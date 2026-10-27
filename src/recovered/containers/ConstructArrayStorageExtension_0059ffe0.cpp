// Original0x0059ffe0: 117 body bytes plus 11 frozenNOP bytes.
// Initial broad real-constructor/array-element model; source identities remain hypotheses.
#include "shared/array_extension_ordinary_views.hpp"

extern "C" unsigned char array_extension_dispatch_0059ffe0[];

ArrayStorageExtension_0059ffe0::ArrayStorageExtension_0059ffe0(int initial_count, ArrayElementExtension_0059ffe0* supplied_storage)
    : ArrayStorageBaseExtension_0059ffe0(initial_count, supplied_storage)
{
    dispatch_table = array_extension_dispatch_0059ffe0;
    unknown_0x14 = 10;
    unknown_0x10 = 0;
}
