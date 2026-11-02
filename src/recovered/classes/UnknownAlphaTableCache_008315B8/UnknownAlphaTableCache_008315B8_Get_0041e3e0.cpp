// AlphaTableRows UnknownAlphaTableCache_008315B8::Get(int count) (0x0041E3E0)
// Returns the shared remap table for a light level, building and registering
// it on first use; each call takes a reference.
#include "shared/alpha_table_cache.hpp"
#include "shared/alpha_lighting_remap.hpp"

AlphaTableRows UnknownAlphaTableCache_008315B8::Get(int count)
{
    for (int index = 0; index < AlphaLightingRemapClass::Array.Count(); index++) {
        if (AlphaLightingRemapClass::Array[index]->Level == count) {
            AlphaLightingRemapClass::Array[index]->RefCount++;
            return (AlphaTableRows)AlphaLightingRemapClass::Array[index]->Table;
        }
    }

    AlphaLightingRemapClass *remap = new AlphaLightingRemapClass(count);
    AlphaLightingRemapClass::Array.Add(remap);
    remap->RefCount++;
    return (AlphaTableRows)remap->Table;
}
