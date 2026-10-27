// void InfantryClass::unknown_slot58(CoordStruct const &coord) (0x00508410, slot 58)
// Occupies the coordinate's spot: on a bridge cell at or above bridge
// height the bridge-level bit and owner, otherwise the ground ones.
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_004763D0@@YIHABUCoordStruct@@@Z=004763d0
// @ref ?unknown_bridge_height_a41120@@3HA=00a41120

void InfantryClass::unknown_slot58(CoordStruct const &coord)
{
    int spot = Unknown_004763D0(coord);
    UnknownCellClass *cell = Map_Cell(coord);
    if (Map.Unknown_0055A280(coord) + unknown_bridge_height_a41120 <= coord.Z && (cell->Flags & 0x100)) {
        cell->unknown_128.Composite |= 1 << spot;
        cell->unknown_58 = Owner();
    } else {
        cell->unknown_124.Composite |= 1 << spot;
        cell->unknown_54 = Owner();
    }
}
