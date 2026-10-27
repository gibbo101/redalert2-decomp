// bool UnitClass::unknown_slot63(Rect *bounds, bool arg2, bool arg3) (0x006FF350, slot 63)
// Not drawn while +0x370 is set and the first contact is a building in or
// queued for mission 16 and the state at +0x2A8 is busy; otherwise the
// object behaviour (with arg3 cleared).
#include "shared/unit.hpp"
// @ref ?Contact_With_Whom@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e20
// @ref ?unknown_slot63@ObjectClass@@UAE_NPAVRect@@_N1@Z=005d34e0
// @ref ?unknown_496a90@UnknownTimed@@QBE_NXZ=00496a90
// @ref ?unknown_496ab0@UnknownTimed@@QBE_NXZ=00496ab0
// @ref ?unknown_496b30@UnknownTimed@@QBE_NXZ=00496b30
// @ref ?unknown_496b50@UnknownTimed@@QBE_NXZ=00496b50

bool UnitClass::unknown_slot63(Rect *bounds, bool arg2, bool arg3)
{
    if (unknown_370) {
        TechnoClass *contact = Contact_With_Whom(0);
        if (contact->Kind_Of() == 6 && (contact->unknown_slot91() == 16 || contact->MissionQueue == 16)) {
            UnknownTimed *state = &contact->unknown_2a8;
            if (state->unknown_496a90() || state->unknown_496ab0() || state->unknown_496b30() || state->unknown_496b50()) {
                return false;
            }
        }
    }
    return ObjectClass::unknown_slot63(bounds, arg2, false);
}
