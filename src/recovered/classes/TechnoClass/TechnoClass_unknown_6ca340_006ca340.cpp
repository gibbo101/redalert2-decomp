// void TechnoClass::unknown_6ca340(int spread) (0x006CA340)
// Draws eight beams (RadBeam type 2, Rules RadColor) from the centre to
// random points of the cells spread cells away in each direction, with
// random period, amplitude and +0x48 value (TechnoClass 0x006CA890).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/rad_beam.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Map@@3VMapClass@@A=008324e0
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_475d60@UnknownCellClass@@QBE?AUCoordStruct@@XZ=00475d60
// @ref ?Allocate@RadBeam@@SIPAV1@H@Z=00635440
// @ref ?Set_Color@RadBeam@@QAEXABVRGBClass@@@Z=00635710
// @ref ?Set_Source@RadBeam@@QAEXABUCoordStruct@@@Z=00635740
// @ref ?Set_Target@RadBeam@@QAEXABUCoordStruct@@@Z=00635760
// @ref ?Set_Period@RadBeam@@QAEXH@Z=00635780
// @ref ?Set_Amplitude@RadBeam@@QAEXN@Z=00635790
// @ref ?unknown_6357b0@RadBeam@@QAEXN@Z=006357b0
// @ref ?unknown_6357d0@RadBeam@@QAEXH@Z=006357d0

void TechnoClass::unknown_6ca340(int spread)
{
    CoordStruct center = Center_Coord();
    int longest = 0;
    Cell cell = Coord_Cell(center);
    RGBClass color = Rules->RadColor;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x != 0 || y != 0) {
                // Each store and multiply is live; this spelling (not Cell(ox, oy)) gives both add destinations.
                int ox = spread * x;
                Cell offset(ox, spread);
                offset.Y *= y;
                Cell spot = offset + cell;
                CoordStruct to = ((UnknownCellClass *)&Map[spot])->unknown_475d60();
                int dx = unknown_random_839218(-128, 128);
                int dy = unknown_random_839218(-128, 128);
                to.X += dx;
                to.Y += dy;
                RadBeam *beam = RadBeam::Allocate(2);
                beam->Set_Color(color);
                int period = unknown_random_839218(5, 20);
                int amplitude = unknown_random_839218(100, 500);
                int value = unknown_random_839218(0, 20);
                beam->Set_Source(center);
                beam->Set_Target(to);
                beam->Set_Period(period);
                beam->Set_Amplitude(amplitude);
                beam->unknown_6357b0(0.0);
                beam->unknown_6357d0(value);
                if (longest <= period) {
                    longest = period;
                }
            }
        }
    }
}
