// void RadarClass::Unknown_00634970(int arg1) (0x00634970)
// Runs 0x00634670 for every house that answers 0x004F52B0 or is not a
// passive multiplayer house, then once more for the last house that
// answered (as index 0) and for the first house (at that index).
#include "shared/radar.hpp"
#include "shared/house_screen.hpp"
#include "shared/house_type.hpp"
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_00634670@RadarClass@@QAEXHHPAVHouseClass@@@Z=00634670

void RadarClass::Unknown_00634970(int arg1)
{
    int last = -1;
    int count = Houses.Count();
    for (int index = 0; index < count; index++) {
        HouseClass *house = Houses[index];
        if (house) {
            if (house->Unknown_004F52B0()) {
                last = index;
            } else if (house->Type->MultiplayPassive) {
                continue;
            }
            Unknown_00634670(arg1, index, house);
        }
    }
    HouseClass *player = Houses[last];
    HouseClass *first = Houses[0];
    Unknown_00634670(arg1, 0, player);
    Unknown_00634670(arg1, last, first);
}
