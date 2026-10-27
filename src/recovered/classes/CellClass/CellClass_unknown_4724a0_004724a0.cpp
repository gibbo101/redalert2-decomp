// void CellClass::unknown_4724a0() (0x004724A0): for a wall overlay, stores
// in +0x50 the owner (slot 14) of the nearest building (ObjectClass
// unknown_5d4c00 distance) that is on the map (+0x74, +0x7D) and belongs to a
// house whose type is a WallOwner; -1 when there is none (MapClass 0x0054B535).
#include "shared/cell.hpp"
#include "shared/overlay_type.hpp"
#include "shared/building_class.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8

void CellClass::unknown_4724a0()
{
    if (OverlayIndex != -1 && OverlayTypes[OverlayIndex]->Wall) {
        int owner = -1;
        int best = 0x7FFFFFFF;
        for (int index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
            BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
            if (building->unknown_7d && building->unknown_74 && building->House->Type->WallOwner) {
                int distance = building->unknown_5d4c00(this);
                if (distance < best) {
                    best = distance;
                    owner = building->Owner();
                }
            }
        }
        unknown_50 = owner;
    }
}
