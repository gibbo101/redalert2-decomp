#include "shared/tunnel_locomotion.hpp"
#include "shared/anim.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60
// @ref ??0AnimClass@@QAE@PAVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref __real@8@3fff8000000000000000=0079a708
// @ref ?Frame@@3HA=00a40d2c

void TunnelLocomotionClass::unknown_6f0530()
{
    if (Timer_Ratio() == 1.0) {
        LinkedTo->unknown_slot306(1.0);
        unknown_18 = 3;
        Voc_Play_At(Rules->unknown_16c, CoordStruct(LinkedTo->Coord), 0);
        new AnimClass(Rules->unknown_228, CoordStruct(LinkedTo->Coord), 0, 1, 0x600, 0);
        LinkedTo->unknown_slot54(false);
    }
}

