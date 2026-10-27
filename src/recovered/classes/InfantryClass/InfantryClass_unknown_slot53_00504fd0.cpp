// bool InfantryClass::unknown_slot53(CoordStruct const *coord, int dir) (0x00504FD0, slot 53)
// Puts the infantry on the map: on the ground it moves to a free spot of
// the cell (alternate spots when 0x00A40774 is set or 0x0055A660 refuses the
// cell) and fails when there is none. After FootClass's slot 53, types
// without Sight clear +0x373, the spot below bridge height is occupied
// (slot 58) and +0x5D0 becomes 2.
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_004764B0@UnknownCellClass@@QAE?AUCoordStruct@@ABU2@H_N@Z=004764b0
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_invalid_coord_a410f8@@3UCoordStruct@@A=00a410f8
// @ref ?unknown_bridge_height_a41120@@3HA=00a41120
// @ref ?unknown_slot53@FootClass@@UAE_NPBUCoordStruct@@H@Z=004c5e40

bool InfantryClass::unknown_slot53(CoordStruct const *coord, int dir)
{
    int ground = Map.Unknown_0055A280(*coord);
    CoordStruct where = *coord;
    if (where.Z == ground) {
        int alternate = unknown_a40774 != 0 || !Map.Unknown_0055A660(Coord_Cell(*coord), true);
        where = Map_Cell(*coord)->Unknown_004764B0(*coord, alternate, false);
        if (where.X == unknown_invalid_coord_a410f8.X && where.Y == unknown_invalid_coord_a410f8.Y
            && where.Z == unknown_invalid_coord_a410f8.Z) {
            return false;
        }
        where.Z = ground;
    }
    if (FootClass::unknown_slot53(&where, dir)) {
        if (Type->Sight == 0) {
            unknown_373 = false;
        }
        if (where.Z <= unknown_bridge_height_a41120 + ground) {
            unknown_slot58(where);
        }
        unknown_5d0 = 2;
        return true;
    }
    return false;
}
