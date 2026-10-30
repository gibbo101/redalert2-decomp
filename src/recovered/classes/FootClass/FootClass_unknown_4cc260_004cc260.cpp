// bool FootClass::unknown_4cc260(Cell &cell, int dx, int dy) (0x004CC260)
// Whether the cell at an offset suits the unit (stored back into cell when
// the map's test 0x0055A660 passes): not a raised spot for a +0x372 unit,
// reachable in the unit's movement zone, unoccupied (slot 101), with land
// type 11 and +0x11E of at least 0x30.
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0054F7C0@MapClass@@QAE_NABVCell@@0H_N11@Z=0054f7c0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_00568140@MapClass@@QAE_NABUCoordStruct@@@Z=00568140
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

bool FootClass::unknown_4cc260(Cell &cell, int dx, int dy)
{
    Cell next = cell + Cell(dx, dy);
    if (Map.Unknown_0055A660(next, true)) {
        cell = next;
        if (unknown_game_mode_a3d298 == 0 && unknown_372) {
            int height = Map.Unknown_0055A280(CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0));
            CoordStruct spot = CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, height);
            if (Map.Unknown_00568140(spot)) {
                return false;
            }
        }
        Cell here = Coord_Cell(unknown_slot19(0));
        if (Map.Unknown_0054F7C0(here, cell, unknown_slot32()->MovementZone, unknown_slot46(0), 0, 0)) {
            CellClass *map_cell = &Map[cell];
            UnknownCellClass *object = (UnknownCellClass *)map_cell;
            if (unknown_slot101(map_cell, -1, -1, 0, 1) == 0 && object->unknown_ec == 11 && object->unknown_11e >= 0x30) {
                return true;
            }
        }
    }
    return false;
}
