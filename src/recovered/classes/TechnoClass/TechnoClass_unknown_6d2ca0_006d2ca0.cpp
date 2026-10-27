// void TechnoClass::unknown_6d2ca0(int x, int y) (0x006D2CA0)
// Sets the draw depth +0x322 from a screen point and the view's Y, raised
// for turret directions 0, 6 (8 pixels) and 7 (12 pixels). Never called:
// inlined at every use.
#include "shared/techno.hpp"
#include "shared/tactical.hpp"
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c

void TechnoClass::unknown_6d2ca0(int x, int y)
{
    unknown_322 = unknown_tactical_83996c->unknown_b0.Y + x + y - 10;
    int dir = Dir_To_8(unknown_2e0.Current());
    if (dir == 0 || dir == 6) {
        unknown_322 -= 8;
    } else if (dir == 7) {
        unknown_322 -= 12;
    }
}
