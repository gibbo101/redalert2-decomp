// bool UnitClass::unknown_slot52() (0x007078F0, slot 52)
// Taking the unit off the map: FootClass's slot 52, and when it succeeds the
// house recorded at +0x5B4 (an index into Houses) hears of the unit's cell
// (0x004E76A0) and the index resets to -1.
#include "shared/unit.hpp"
#include "shared/house.hpp"
// @ref ?unknown_slot52@FootClass@@UAE_NXZ=004c9bd0
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?unknown_4e76a0@HouseClass@@QAEXABVCell@@H@Z=004e76a0

bool UnitClass::unknown_slot52()
{
    if (FootClass::unknown_slot52()) {
        if (unknown_5b4 != -1) {
            Houses[unknown_5b4]->unknown_4e76a0(unknown_slot104(), 0);
            unknown_5b4 = -1;
        }
        return true;
    }
    return false;
}
