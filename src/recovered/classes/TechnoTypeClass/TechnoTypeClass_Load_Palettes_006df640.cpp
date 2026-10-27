// static void TechnoTypeClass::Load_Palettes() (0x006DF640)
// Load_Palette for every type. Not in the function inventory: the gap
// 0x006DF640-0x006DF67F holds this body (61 bytes) and padding.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?TechnoTypes@@3V?$DynamicVectorClass@PAVTechnoTypeClass@@@@A=00a40ab8
// @ref ?Load@PaletteName@@QAEPAXXZ=00603380

void TechnoTypeClass::Load_Palettes()
{
    for (int index = 0; index < TechnoTypes.Count(); index++) {
        TechnoTypes[index]->Load_Palette();
    }
}
