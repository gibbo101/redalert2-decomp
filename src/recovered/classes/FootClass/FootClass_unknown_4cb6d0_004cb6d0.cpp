// bool FootClass::unknown_4cb6d0(Cell const &cell) (0x004CB6D0)
// Whether a cell suits the unit (cf. 0x004CC260): passes the map test
// 0x0055A660, is not a raised spot for a +0x372 unit, is reachable in the
// unit's movement zone, has land type 5 and is unoccupied (slot 101).
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0054F7C0@MapClass@@QAE_NABVCell@@0H_N11@Z=0054f7c0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_00568140@MapClass@@QAE_NABUCoordStruct@@@Z=00568140
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

bool FootClass::unknown_4cb6d0(Cell const &cell)
{
    if (Map.Unknown_0055A660(cell, true)) {
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
            if (object->unknown_ec == 5 && unknown_slot101(map_cell, -1, -1, 0, 1) == 0) {
                return true;
            }
        }
    }
    return false;
}
