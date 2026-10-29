// bool HouseClass::unknown_func_4e7070(TechnoClass *builder, BuildingClass *building) (0x004E7070)
// RA's Manual_Place: the player's house, with nothing pending, starts placing
// a finished building: the selection is cleared, the repair and sell modes
// end, the building, its type and the house become the map's pending
// placement, the cursor takes the building's foundation list and moves to
// the builder's cell, and the builder is marked (slot 71).
#include "shared/techno.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Clear_Selected_Objects_00482bc0@@YAXXZ=00482bc0
// @ref ?Unknown_00498F10@DisplayClass@@QAEXPBVCell@@@Z=00498f10
// @ref ?Unknown_004994D0@DisplayClass@@QAE?AVCell@@ABV2@@Z=004994d0
void __cdecl Clear_Selected_Objects_00482bc0();

bool HouseClass::unknown_func_4e7070(TechnoClass *builder, BuildingClass *building)
{
    if (this == unknown_player_a35db4 && Map.unknown_11a4 == 0 && builder != 0 && building != 0) {
        Clear_Selected_Objects_00482bc0();
        Map.Unknown_0049CA20(0);
        Map.Unknown_0049C7C0(0);
        Map.unknown_11ae = false;
        Map.unknown_11af = false;
        Map.unknown_11b0 = false;
        Map.unknown_11b4 = -1;
        Map.unknown_11a4 = building->Type;
        Map.unknown_11a0 = building;
        Map.unknown_11a8 = ArrayIndex;
        Map.Unknown_00498F10(building->unknown_slot64(1));
        Map.Unknown_004994D0(builder->unknown_slot104());
        builder->unknown_slot71(2);
        return true;
    }
    return false;
}
