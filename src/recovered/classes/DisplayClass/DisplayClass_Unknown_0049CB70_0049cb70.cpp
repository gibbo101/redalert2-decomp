// CoordStruct DisplayClass::Unknown_0049CB70(CoordStruct const &coord, bool any) (0x0049CB70)
// The free infantry spot of the map's cell at a coordinate; the last
// argument is set when the cell has the bridge flag (+0x140 bit 8) and the
// coordinate lies at or above the bridge deck (the cell's level plus four,
// scaled).
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_geometry_g@@3HA=00852948
// @ref ?Closest_Free_Spot@CellClass@@QBE?AUCoordStruct@@ABU2@_NH@Z=004764b0
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000

CoordStruct DisplayClass::Unknown_0049CB70(CoordStruct const &coord, bool any)
{
    CellClass &cell = Map[coord];
    return cell.Closest_Free_Spot(coord, any,
                                  (cell.unknown_140 & 0x100) && coord.Z >= (cell.unknown_11b + 4) * unknown_geometry_g ? 1 : 0);
}
