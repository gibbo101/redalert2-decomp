// bool UnitClass::INoticeSink_Unknown(int code, int arg) (0x00709890;
// UnitClass's INoticeSink vtable 0x007ADDD4, `this` adjusted from the +8
// subobject)
// Notice 0x117B for a BalloonHover or JumpJet type in radio contact: tell
// the contact message 8, then attack the target at +0x1B0 unless it is the
// navigation target (+0x494), otherwise clear the navigation and move to the
// zero coordinate. Notice 0x117C for a Crashable type: slot 109 (0), the
// death explosion (or, for a BalloonHover type, the death weapon) and slot
// 60. True when handled. (InfantryClass 0x00509590 is the same notice pair.)
#include "shared/unit.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Unknown_004CD9B0@FootClass@@QAEXXZ=004cd9b0

bool UnitClass::INoticeSink_Unknown(int code, int arg)
{
    if ((Type->BalloonHover || Type->JumpJet) && code == 0x117B && In_Radio_Contact()) {
        unknown_slot149(8);
        if (unknown_1b0 != 0 && unknown_1b0 != unknown_494) {
            unknown_slot260(unknown_1b0, 1);
            return true;
        }
        Unknown_004CD9B0();
        unknown_slot87(unknown_geometry_l, true, false);
        return true;
    }
    if (Type->Crashable && code == 0x117C) {
        unknown_slot109(0);
        if (!Type->BalloonHover) {
            unknown_6fd3a0();
        } else {
            unknown_6d7e20(0);
        }
        unknown_slot60();
        return true;
    }
    return false;
}
