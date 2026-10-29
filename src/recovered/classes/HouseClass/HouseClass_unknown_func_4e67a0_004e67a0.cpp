// void HouseClass::unknown_func_4e67a0(int index) (0x004E67A0)
// Picks the building of another, non-allied house with the highest slot 90
// value (each candidate passes a 90% roll; buildings with no strength or the
// +0x76 flag are skipped) and hands its cell to 0x004E68D0.
#include "shared/techno.hpp"
#include "shared/id_source.hpp"

void HouseClass::unknown_func_4e67a0(int index)
{
    BuildingClass *best = 0;
    int value = -1;
    for (int i = 0; i < unknown_BuildingClass_list_00a40af8.Count(); i++) {
        BuildingClass *building = unknown_BuildingClass_list_00a40af8[i];
        if (building != 0 && !building->unknown_76 && building->Strength != 0 && !Is_Ally(building)
                && Random_Pick(0, 99) < 90) {
            if (building->unknown_slot90() > value || value == -1) {
                value = building->unknown_slot90();
                best = building;
            }
        }
    }
    if (best != 0) {
        Cell cell = Coord_Cell(best->Center_Coord());
        unknown_func_4e68d0(index, cell);
    }
}
