// bool UnitClass::unknown_slot53(CoordStruct const *coord, int dir) (0x006FC940, slot 53: Unlimbo)
// The foot placement, then the turret faces dir (a 0..255 direction); a
// cloakable unit not yet cloaked starts in state 2 (+0x1B8); visceroids
// start the +0xE0 counter at a random 0..29 with a one-frame timer,
// everything else at zero.
#include "shared/unit.hpp"
// @ref ?unknown_slot53@FootClass@@UAE_NPBUCoordStruct@@H@Z=004c5e40
// @ref ?Set_Current@FacingClass@@QAEXABUUnknownFacingDir@@@Z=004b8b10
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

bool UnitClass::unknown_slot53(CoordStruct const *coord, int dir)
{
    if (FootClass::unknown_slot53(coord, dir)) {
        unknown_2f8.Set_Current(UnknownFacingDir((unsigned short)(dir << 8)));
        if (unknown_32a && !unknown_32d) {
            unknown_1b8 = 2;
        }
        if (!Type->SmallVisceroid && !Type->LargeVisceroid) {
            AnimationStage.Value = 0;
            AnimationStage.Timer = CDTimerClass<FrameTimerClass>(0);
            AnimationStage.unknown_10 = 0;
            return true;
        }
        AnimationStage.Value = unknown_id_source_a3d290->Random()(0, 29);
        AnimationStage.Timer = CDTimerClass<FrameTimerClass>(1);
        AnimationStage.unknown_10 = 1;
        return true;
    }
    return false;
}
