// void JumpjetLocomotionClass::unknown_52fca0() (0x0052FCA0)
// Takes off when moving: the object's slot 306 ratio goes to 1.0, the
// facing (+0x50) is set to the object's facing (+0x2E0), both speeds (+0x68,
// +0x70) are cleared and the target height (+0x78) becomes the jumpjet
// height; unless the owner's house holds the locomotors (0x0051FC80), an
// object at no cell is reported to the arrival tracker and the state
// (+0x4C) becomes 1.
#include "shared/jumpjet_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/house.hpp"
// @ref ?Unknown_004131E0@UnknownTracker839EA0@@QAEXPAVFootClass@@@Z=004131e0
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0

void JumpjetLocomotionClass::unknown_52fca0()
{
    if (Is_Moving()) {
        LinkedTo->unknown_slot306(1.0);
        unknown_50.Set_Current(LinkedTo->unknown_2e0.Current());
        unknown_68 = 0;
        unknown_70 = 0;
        unknown_78 = Height;
        if (!LinkedTo->House->Unknown_0051FC80()) {
            if (LinkedTo->unknown_slot178() == unknown_geometry_k) {
                unknown_tracker_839ea0.Unknown_004131E0(LinkedTo);
            }
            unknown_4c = 1;
        }
    }
}
