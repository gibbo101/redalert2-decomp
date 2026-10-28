#include "shared/tunnel_locomotion.hpp"
#include "shared/anim.hpp"
#include "shared/fast_math.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60
// @ref ??0AnimClass@@QAE@PAVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ?Is_Rotating@FacingClass@@QBE_NXZ=004b8c90
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref __ftol=0077f110
// @ref __real@8@40058000000000000000=007adca0

// The direction from one coordinate to another (hypothesis: Westwood's Direction()).
static inline UnknownFacingDir Coord_Direction(CoordStruct const &from, CoordStruct const &to)
{
    CoordStruct delta = from;
    delta.X = to.X - delta.X;
    delta.Y = to.Y - delta.Y;
    double angle = Fast_Atan2((double)-delta.Y, (double)delta.X);
    return UnknownFacingDir((unsigned short)(int)((angle - 1.5707963267948966) * -10430.060040584269));
}

void TunnelLocomotionClass::unknown_6f03b0()
{
    if (!LinkedTo->unknown_2e0.Is_Rotating()) {
        UnknownFacingDir dir = Coord_Direction(LinkedTo->Coord, unknown_1c);
        if (dir.Raw != LinkedTo->unknown_2e0.Current().Raw) {
            Do_Turn(dir);
            return;
        }
        int delay = (int)(64.0 / LinkedTo->unknown_slot32()->ROT / Rules->unknown_20);
        unknown_28 = UnknownTunnelTimer(delay);
        unknown_18 = 2;
        Voc_Play_At(Rules->unknown_16c, CoordStruct(LinkedTo->Coord), 0);
        new AnimClass(Rules->unknown_228, CoordStruct(LinkedTo->Coord), 0, 1, 0x600, 0);
        unknown_38 = false;
    }
}

