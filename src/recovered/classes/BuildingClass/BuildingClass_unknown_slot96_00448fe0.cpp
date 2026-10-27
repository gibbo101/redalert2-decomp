// bool BuildingClass::unknown_slot96(HouseClass *house) (0x00448FE0)
// The techno's slot 96 first (false stops here). Outside the special mode
// (unknown_a40774 clear) the owner records this type's index and its flag
// at +0x18D; the owner's +0x144 is set. A building not in radio contact then
// runs slot 282(false) when its owner passes 0x004F52F0 and neither its
// slot 91 nor its queued mission is 0x12, or when the owner fails it, the
// house argument is the owner and slot 91 is not 0x12.
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?unknown_slot96@TechnoClass@@UAE_NPAVHouseClass@@@Z=006c2440
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref _unknown_a40774=00a40774

bool BuildingClass::unknown_slot96(HouseClass *house)
{
    if (TechnoClass::unknown_slot96(house)) {
        if (unknown_a40774 == 0) {
            House->unknown_1b4 = Type->ArrayIndex;
            House->unknown_18d = true;
        }
        House->unknown_144 = true;
        if (!In_Radio_Contact() && House->Unknown_004F52F0() && unknown_slot91() != 0x12 && MissionQueue != 0x12) {
            unknown_slot282(false);
        } else if (!In_Radio_Contact() && !House->Unknown_004F52F0() && house == House && unknown_slot91() != 0x12) {
            unknown_slot282(false);
        }
        return true;
    }
    return false;
}
