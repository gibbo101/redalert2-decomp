// bool InfantryClass::INoticeSink_Unknown(int code, int arg) (0x00509590;
// InfantryClass's INoticeSink vtable 0x007A351C, `this` adjusted from the
// +8 subobject)
// Notice 0x117B for a BalloonHover or JumpJet type in radio contact: tell
// the contact message 8, then attack the target at +0x1B0 unless it is the
// navigation target (+0x494), otherwise clear the navigation and move to the
// invalid coordinate. Notice 0x117C for a Crashable type: slot 109 (0) and
// sequence 0x24. True when handled.
#include "shared/infantry.hpp"
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Unknown_004CD9B0@FootClass@@QAEXXZ=004cd9b0
// @ref ?unknown_invalid_coord_a410f8@@3UCoordStruct@@A=00a410f8

bool InfantryClass::INoticeSink_Unknown(int code, int arg)
{
    if ((Type->BalloonHover || Type->JumpJet) && code == 0x117B && In_Radio_Contact()) {
        unknown_slot149(8);
        if (unknown_1b0 != 0 && unknown_1b0 != unknown_494) {
            unknown_slot260(unknown_1b0, 1);
            return true;
        }
        Unknown_004CD9B0();
        unknown_slot87(unknown_invalid_coord_a410f8, true, false);
        return true;
    }
    if (Type->Crashable && code == 0x117C) {
        unknown_slot109(0);
        unknown_slot311(0x24, 1, 0);
        return true;
    }
    return false;
}
