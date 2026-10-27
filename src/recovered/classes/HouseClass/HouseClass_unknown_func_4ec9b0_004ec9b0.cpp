// void HouseClass::unknown_func_4ec9b0() (0x004EC9B0)
// Redraws (slot 71) every building whose type sets +0xC68 and whose +0x1A8
// mask includes the player's house type.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

void HouseClass::unknown_func_4ec9b0()
{
    int count = unknown_objects_a40c60.Count();
    if (count != 0) {
        for (int index = 0; index < count; index++) {
            UnknownBuildingView *building = (UnknownBuildingView *)unknown_objects_a40c60[index];
            if (building != 0 && building->Kind_Of() == 6 && !building->unknown_372 &&
                ((UnknownBuildingTypeView *)building->Type)->unknown_c68 > 0 &&
                (building->unknown_1a8 & (1 << unknown_player_a35db4->Type->House)) != 0) {
                building->unknown_slot71(2);
            }
        }
    }
}
