// Clears the infantry occupancy bit at a coordinate (0x005084A0).
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_004763D0@@YIHABUCoordStruct@@@Z=004763d0
// @ref ?unknown_bridge_height_a41120@@3HA=00a41120
void InfantryClass::unknown_slot59(CoordStruct const &coord)
{
    int spot = Unknown_004763D0(coord);
    UnknownCellClass *cell = Map_Cell(coord);
    int ground_height = Map.Unknown_0055A280(coord);
    if (unknown_bridge_height_a41120 + ground_height <= coord.Z) {
        cell->unknown_128.Composite &= ~(1 << spot);
        if ((cell->unknown_128.Composite & 0x1c) == 0) {
            cell->unknown_58 = -1;
        }
    } else {
        cell->unknown_124.Composite &= ~(1 << spot);
        if ((cell->unknown_124.Composite & 0x1c) == 0) {
            cell->unknown_54 = -1;
        }
    }
}
