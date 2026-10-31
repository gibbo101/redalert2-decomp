// int ParticleClass::unknown_slot116() (0x0060A670)
// The shape frame: behaviours 0 and 1 use unknown_11e; behaviour 2 adds the
// type's per-direction frame count (+0x2D9) times 0..3 by the screen
// direction from the start (unknown_e4) to the target (unknown_d8).
#include "shared/particle.hpp"
// @ref ?Coord_To_Pixel@Tactical@@QAE_NABUCoordStruct@@PAUPoint2D@@@Z=006a29d0
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_00721DB0@@YIHABUPoint2D@@0@Z=00721db0

int ParticleClass::unknown_slot116()
{
    switch (Class->BehavesLike) {
    case 0:
    case 1:
        return unknown_11e;
    case 2:
        {
            Point2D from;
            Point2D to;
            unknown_tactical_83996c->Coord_To_Pixel(unknown_e4, from);
            unknown_tactical_83996c->Coord_To_Pixel(unknown_d8, to);
            int direction = Unknown_00721DB0(from, to);
            if (direction == 2 || direction == 6) {
                return unknown_11e + Class->EndStateAI * 2;
            }
            if (direction == 4 || direction == 0) {
                return unknown_11e;
            }
            if (direction == 1 || direction == 5) {
                return Class->EndStateAI + unknown_11e;
            }
            if (direction == 3 || direction == 7) {
                return Class->EndStateAI * 3 + unknown_11e;
            }
        }
        break;
    }
    return 0;
}
