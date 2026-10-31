// Cell HouseClass::Unknown_004EB270(FootClass *foot) (0x004EB270)
// RA's Where_To_Go: a unit without weapons goes to the core zone, others to
// a random outer zone; the cell is the reachable one (tracked) nearest a
// random cell of that zone, in the zone of the unit's own cell.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/techno.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Random_Cell_In_Zone@HouseClass@@QAE?AVCell@@H@Z=004eca50
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@11110H@Z=005502e0

inline Cell Coord_Cell_Value(CoordStruct coord)
{
    return Coord_Cell(coord);
}

Cell HouseClass::Unknown_004EB270(FootClass *foot)
{
    int zone;
    if (foot->unknown_6d59d0() + foot->unknown_6d5900() + foot->unknown_6d5870() == 0) {
        zone = 0;
    } else {
        zone = Random_Pick(1, 4);
    }
    Cell cell = Random_Cell_In_Zone(zone);
    return Map.Unknown_005502E0(cell, 1, Map.Zone(Coord_Cell_Value(foot->Coord), 0, false), 0, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
}
