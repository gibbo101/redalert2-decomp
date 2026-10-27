// Original0x00682580: 117 body bytes plus 11 frozenNOP bytes.
// Initial broad real-constructor/array-element model; source identities remain hypotheses.
#include "shared/array_extension_ordinary_views.hpp"

extern "C" unsigned char array_extension_dispatch_00682580[];

ArrayStorageExtension_00682580::ArrayStorageExtension_00682580(int initial_count, ArrayElementExtension_00682580* supplied_storage)
    : ArrayStorageBaseExtension_00682580(initial_count, supplied_storage)
{
    dispatch_table = array_extension_dispatch_00682580;
    unknown_0x14 = 10;
    unknown_0x10 = 0;
}
