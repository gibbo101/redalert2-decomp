// void TerrainClass::unknown_slot59(CoordStruct const &coord) (0x006E3850)
// Clears the cell's terrain occupation bits named by the type's
// occupation bits for the theater (snow: SnowOccupationBits).
#include "shared/terrain.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Map@@3VMouseClass@@A=008324e0

void TerrainClass::unknown_slot59(CoordStruct const &coord)
{
    int bits;
    if (unknown_id_source_a3d290->Theater != 1) {
        bits = Class->TemperateOccupationBits;
    } else {
        bits = Class->SnowOccupationBits;
    }
    CellClass &cell = Map_Cell(Coord_Cell(coord));
    if (bits & 1) {
        cell.unknown_124 &= ~0x04;
    }
    if (bits & 2) {
        cell.unknown_124 &= ~0x08;
    }
    if (bits & 4) {
        cell.unknown_124 &= ~0x10;
    }
}
