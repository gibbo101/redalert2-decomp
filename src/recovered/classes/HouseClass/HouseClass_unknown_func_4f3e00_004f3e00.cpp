// void HouseClass::unknown_func_4f3e00(SuperClass *super) (0x004F3E00)
// Fires a super weapon (0x004E68D0) at the building of the house the
// computer is angry at (+0x54F0) whose cell rates highest for this house
// (0x0054E3A0; a building with +0x5BD 15 rates at random up to 100).
#include "shared/techno.hpp"
#include "shared/map_view.hpp"
#include "shared/id_source.hpp"

void HouseClass::unknown_func_4f3e00(SuperClass *super)
{
    if (unknown_54f0 != -1) {
        BuildingClass *best = 0;
        int value = -1;
        HouseClass *house = Houses[unknown_54f0];
        for (int i = unknown_BuildingClass_list_00a40af8.Count() - 1; i >= 0; i--) {
            BuildingClass *building = unknown_BuildingClass_list_00a40af8[i];
            if (building->House == house) {
                int rating = Map.Unknown_0054E3A0(Coord_Cell(building->Center_Coord()), this);
                if (building->unknown_5bd == 15) {
                    rating = Random_Pick(0, 100);
                }
                if (rating > value) {
                    value = rating;
                    best = building;
                }
            }
        }
        if (best != 0) {
            unknown_func_4e68d0(Supers.ID(super), Coord_Cell(best->Center_Coord()));
        }
    }
}
