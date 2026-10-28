// void FlyLocomotionClass::Start_Drift() (0x004BF550)
// A drift of 20..30, either way at random. Power_Off expands it; this
// out-of-line copy is never called.
#include "shared/fly_locomotion.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0

void FlyLocomotionClass::Start_Drift()
{
    unknown_53 = true;
    unknown_54 = unknown_id_source_a3d290->Random()(20, 30);
    if (unknown_id_source_a3d290->Random()(0, 99) < 50) {
        unknown_54 = -unknown_54;
    }
}
