// Cell RadarClass::unknown_slot51(Point2D const &xy) (0x0062FBD0, slot 51)
// The cell under a screen point: the cached cell (0x00AB6330) when the point
// maps to the cached coordinate (0x00AB6370), else the tactical view's cell.
// Both branches on the flag at 0x00A40D13 compile to the same call.
#include "shared/radar.hpp"
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A2B10@Tactical@@QAE?AUCoordStruct@@ABUPoint2D@@@Z=006a2b10
// @ref ?Unknown_006A6BD0@Tactical@@QAE?AVCell@@ABUPoint2D@@@Z=006a6bd0
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?unknown_cell_ab6330@RadarClass@@2VCell@@A=00ab6330
// @ref ?unknown_coord_ab6370@RadarClass@@2UCoordStruct@@A=00ab6370

Cell RadarClass::unknown_slot51(Point2D const &xy)
{
    Point2D point = xy;
    CoordStruct coord = unknown_tactical_83996c->Unknown_006A2B10(point);
    if (coord != unknown_coord_ab6370) {
        if (unknown_flag_a40d13) {
            return unknown_tactical_83996c->Unknown_006A6BD0(point);
        }
        return unknown_tactical_83996c->Unknown_006A6BD0(point);
    }
    return unknown_cell_ab6330;
}
