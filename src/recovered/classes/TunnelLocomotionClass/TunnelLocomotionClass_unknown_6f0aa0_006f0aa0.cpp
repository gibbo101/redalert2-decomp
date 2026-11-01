#include "shared/tunnel_locomotion.hpp"
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60
// @ref ??0AnimClass@@QAE@PBVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref __ftol=0077f110
// @ref __real@8@40058000000000000000=007adca0

void TunnelLocomotionClass::unknown_6f0aa0()
{
    CoordStruct coord = LinkedTo->Coord;
    int ground = Map.Unknown_0055A280(coord);
    if (coord.Z < ground) {
        int height = LinkedTo->unknown_slot108();
        int rate = (int)(LinkedTo->unknown_slot303() * Rules->unknown_20);
        if (rate <= 5) {
            rate = 5;
        }
        coord.Z += rate;
        if (coord.Z > ground) {
            coord.Z = ground;
        }
        LinkedTo->unknown_slot103(coord);
        if (height <= -0x32 && LinkedTo->unknown_slot108() > -0x32) {
            Voc_Play_At(Rules->unknown_16c, CoordStruct(LinkedTo->Coord), 0);
            new AnimClass(Rules->unknown_228, CoordStruct(LinkedTo->Coord), 0, 1, 0x600, 0);
        }
    } else {
        LinkedTo->unknown_slot70(0, 0);
        int delay = (int)(64.0 / LinkedTo->unknown_slot32()->ROT);
        unknown_28 = UnknownTunnelTimer(delay);
        LinkedTo->unknown_slot306(0.0);
        unknown_18 = 6;
    }
}

