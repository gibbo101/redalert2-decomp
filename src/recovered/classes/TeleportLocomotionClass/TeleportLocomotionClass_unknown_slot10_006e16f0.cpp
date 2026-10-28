// void __stdcall TeleportLocomotionClass::unknown_slot10() (0x006E16F0, IPersistStream-side slot 10)
// When the warp timer has run out the linked object's +0x205 is cleared
// and a running count at +0x38 advances.
#include "shared/teleport_locomotion.hpp"

void __stdcall TeleportLocomotionClass::unknown_slot10()
{
    if (unknown_3c.Value() == 0) {
        LinkedTo->unknown_205 = false;
        if (unknown_38 > 0) {
            unknown_38++;
        }
    }
}
