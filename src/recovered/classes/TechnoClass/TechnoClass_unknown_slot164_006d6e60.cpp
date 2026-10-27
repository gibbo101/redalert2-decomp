// int TechnoClass::unknown_slot164() (0x006D6E60, slot 164)
// 0 when the tactical view shows the coordinate in the techno's own cell
// (slot 104), else 1.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A6A50@UnknownTacticalView@@QAE?AVCell@@ABUCoordStruct@@@Z=006a6a50

int TechnoClass::unknown_slot164()
{
    CoordStruct coord = Coord;
    Cell shown = ((UnknownTacticalView *)unknown_tactical_83996c)->Unknown_006A6A50(coord);
    if (shown == unknown_slot104()) {
        return 0;
    }
    return 1;
}
