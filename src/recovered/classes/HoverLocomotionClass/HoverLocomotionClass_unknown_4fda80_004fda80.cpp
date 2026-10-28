// void HoverLocomotionClass::unknown_4fda80() (0x004FDA80)
// Stops: no speed (+0x48, +0x50 and the object's slot 306) and no head-to
// coordinate (its mark cleared, slot 59). Expanded where it is used; this
// out-of-line copy is never called.
#include "shared/hover_locomotion.hpp"
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080

void HoverLocomotionClass::unknown_4fda80()
{
    unknown_50 = 0;
    unknown_48 = 0;
    LinkedTo->unknown_slot306(0);
    if (unknown_24 != unknown_coord_a41080) {
        LinkedTo->unknown_slot59(unknown_24);
        unknown_24 = unknown_coord_a41080;
    }
}
