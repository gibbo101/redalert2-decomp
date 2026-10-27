// void UnitClass::unknown_slot58(CoordStruct const &coord) (0x00707980, slot 58)
// Sets the vehicle occupation bit (0x20) of the cell at coord: the bridge level's (+0x128)
// when coord is at or above the bridge height (0x00AD057C) over a bridge cell, else the
// ground's (+0x124). ObjectClass slot 58 (0x005D4960) does the same with the 0x40 bit.
#include "shared/unit.hpp"
#include "shared/techno_map.hpp"
// @ref ?unknown_bridge_height_ad057c@@3HA=00ad057c

// The height a bridge adds (0x00AD057C).
extern int unknown_bridge_height_ad057c;

void UnitClass::unknown_slot58(CoordStruct const &coord)
{
    UnknownCellClass *cell = Map_Cell(coord);
    if (Map.Unknown_0055A280(coord) + unknown_bridge_height_ad057c <= coord.Z && (cell->Flags & 0x100)) {
        cell->unknown_128.Occupy.Vehicle = true;
    } else {
        cell->unknown_124.Occupy.Vehicle = true;
    }
}
