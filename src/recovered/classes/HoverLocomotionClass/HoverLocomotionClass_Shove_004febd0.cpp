// bool __stdcall HoverLocomotionClass::Shove(UnknownFacingDir dir) (0x004FEBD0, ILocomotion 27)
// A successful push also starts a drift.
#include "shared/hover_locomotion.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0

bool __stdcall HoverLocomotionClass::Shove(UnknownFacingDir dir)
{
    if (Push(dir)) {
        unknown_68 = true;
        unknown_6c = unknown_id_source_a3d290->Random()(20, 30);
        if (unknown_id_source_a3d290->Random()(0, 99) < 50) {
            unknown_6c = -unknown_6c;
        }
        return true;
    }
    return false;
}
