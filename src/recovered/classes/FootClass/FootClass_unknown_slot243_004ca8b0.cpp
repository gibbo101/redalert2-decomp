// void FootClass::unknown_slot243(bool force, int arg2) (0x004CA8B0)
// Draws the line from the unit to its target (or to the last queued
// destination, lifted onto a bridge's height) in colours taken from the
// drawer's table: skipped unless forced while the timer at 0x00AC0178 runs.
#include "shared/foot.hpp"
#include "shared/convert.hpp"
#include "shared/hicolor.hpp"
#include "shared/map_view.hpp"
#include "shared/gadget.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_timer_ac0178@@3V?$CDTimerClass@VFrameTimerClass@@@@A=00ac0178
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?unknown_6d65b0@TechnoClass@@QAE?AUCoordStruct@@XZ=006d65b0
// @ref ?unknown_6d0510@TechnoClass@@QAEXUCoordStruct@@0VRGBClass@@HH@Z=006d0510
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref _unknown_geometry_j=00865f60

void FootClass::unknown_slot243(bool force, int arg2)
{
    CoordStruct from;
    CoordStruct to;
    if (unknown_228 != 0 || unknown_494 != 0) {
        if (!force && unknown_timer_ac0178.Value() <= 0) {
            return;
        }
        if (unknown_228 != 0) {
            from = unknown_slot181(0);
            to = unknown_6d65b0();
            unknown_6d0510(from, to, Unpack_Hicolor_Pixel(unknown_drawer_8323c4->Convert(8)), 0, 0);
            return;
        }
        from = Coord;
        if (unknown_478.Count() == 0) {
            to = unknown_494->Center_Coord();
        } else {
            to = unknown_478[unknown_478.Count() - 1]->Center_Coord();
        }
        if (Map.Unknown_0054AAB0(Coord_Cell(to)) && (((UnknownCellClass *)&Map[to])->Flags & 0x100)) {
            to.Z = Map.Unknown_0055A280(to) + unknown_geometry_j;
        }
        unknown_6d0510(from, to, Unpack_Hicolor_Pixel(unknown_drawer_8323c4->Convert(3)), arg2, 0);
    }
}
