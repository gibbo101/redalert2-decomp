// void UnknownAlphaTableCache_008315B8::Release(AlphaTableRows table) (0x0041E510)
// Drops a reference to a shared remap table; the last one unregisters and
// frees it.
#include "shared/alpha_table_cache.hpp"
#include "shared/alpha_lighting_remap.hpp"

void UnknownAlphaTableCache_008315B8::Release(AlphaTableRows table)
{
    if (table != 0) {
        AlphaLightingRemapClass *remap = (AlphaLightingRemapClass *)table;
        remap->RefCount--;
        if (remap->RefCount == 0) {
            AlphaLightingRemapClass::Array.Delete(remap);
            delete remap;
        }
    }
}
