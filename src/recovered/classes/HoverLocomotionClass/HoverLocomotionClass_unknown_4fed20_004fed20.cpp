// void HoverLocomotionClass::unknown_4fed20() (0x004FED20)
// Full speed (+0x48 and the object's slot 306), the 0x004FE0F0 step, then
// 0x004FCBC0 unless the object already stands in the head-to cell.
// Expanded where it is used; this out-of-line copy is never called.
#include "shared/hover_locomotion.hpp"
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080
// @ref ?Start_Of_Move_004fe0f0@HoverLocomotionClass@@QAEXH@Z=004fe0f0
// @ref ?While_Moving_004fcbc0@HoverLocomotionClass@@QAEH_N@Z=004fcbc0

void HoverLocomotionClass::unknown_4fed20()
{
    bool arrived = unknown_24 == unknown_coord_a41080 || LinkedTo->unknown_slot104() == unknown_24.As_Cell();
    unknown_48 = 1.0;
    LinkedTo->unknown_slot306(1.0);
    Start_Of_Move_004fe0f0(0);
    if (arrived) {
        While_Moving_004fcbc0(true);
    }
}
