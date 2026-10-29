// AbstractClass *HouseClass::unknown_func_4eb360(CoordStruct const &coord) (0x004EB360)
// RA's Find_Juicy_Target, around a coordinate: of the units in the 369 cells
// nearest its cell (rings of unknown_cells_a6f248) that are not allied, stand
// outside their owner's zones, have slot 108 at least -20 and +0x1B8 not 2,
// the nearest (anti-air units count double distance).
#include "shared/techno.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/coord_distance.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?unknown_cells_a6f248@@3PAVCell@@A=00a6f248
// @ref ?unknown_cell_count_7a5934@@3HA=007a5934

extern Cell unknown_cells_a6f248[369];      // 0x00A6F248 (cell offsets in rings around 0, 0)
extern int unknown_cell_count_7a5934;       // 0x007A5934 (369, their count)

AbstractClass *HouseClass::unknown_func_4eb360(CoordStruct const &coord)
{
    TechnoClass *best = 0;
    int value = 0;
    Cell center = Coord_Cell(coord);
    int count = unknown_cell_count_7a5934;
    for (int index = 0; index < count; index++) {
        TechnoClass *unit = (TechnoClass *)Map[center + unknown_cells_a6f248[index]].Cell_Unit(true);
        if (unit != 0 && !unit->unknown_76 && !Is_Ally(unit) && unit->House->Which_Zone(unit) == -1
                && unit->unknown_slot108() >= -20 && unit->unknown_1b8 != 2) {
            int distance = Coord_Distance(coord, unit->Center_Coord());
            if (unit->unknown_6d5870() != 0) {
                distance *= 2;
            }
            if (value == 0 || distance < value) {
                value = distance;
                best = unit;
            }
        }
    }
    if (best != 0) {
        return best;
    }
    return 0;
}
