// 0x0044E570: clear the laser-fence post DWORD at +4EC when the global gate is zero.
// Free/static ownership and the original developer name remain unknown.
#include "shared/building.hpp"

void __fastcall Building_Reset_Fence_Progress_0044e570(BuildingClass *building)
{
    if(!unknown_a40774 && building->Type->LaserFencePost)
        building->unknown_4ec=0;
}
