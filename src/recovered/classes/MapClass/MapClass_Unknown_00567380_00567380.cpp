// void MapClass::Unknown_00567380() (0x00567380)
// Gives every wall overlay cell an owner (TibSun Initialize_Wall_Ownership):
// the house of the nearest building (ObjectClass 0x005D4C00) that is +0x7D and
// +0x74 and whose house type is a WallOwner goes into the cell's +0x50.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/house_screen.hpp"
#include "shared/map_techno.hpp"
#include "shared/overlay_view.hpp"
// @ref ?unknown_5d4c00@TechnoClass@@QAEHPAVCellClass@@@Z=005d4c00
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8
// @ref ?unknown_overlay_types_a35de8@@3V?$DynamicVectorClass@PAVUnknownOverlayType@@@@A=00a35de8

void MapClass::Unknown_00567380()
{
    Unknown_0055A550();
    CellClass *cellptr = Unknown_0055A490();
    while (cellptr != 0) {
        if (cellptr->OverlayIndex != -1) {
            if (unknown_overlay_types_a35de8[cellptr->OverlayIndex]->unknown_278) {
                int best = -1;
                int index = 0;
                int bestdist = 0x7FFFFFFF;
                for (index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
                    BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
                    int distance = building->unknown_5d4c00(cellptr);
                    if (building->unknown_7d && building->unknown_74 && building->House->Type->WallOwner) {
                        if (best == -1 || distance < bestdist) {
                            bestdist = distance;
                            best = index;
                        }
                    }
                }
                if (best != -1) {
                    cellptr->unknown_50 = unknown_BuildingClass_list_00a40af8[best]->House->ArrayIndex;
                }
            }
        }
        cellptr = Unknown_0055A490();
    }
}
