// CoordStruct CellClass::unknown_slot22() const (0x0047BAA0, slot 22): the
// cell's centre (slot 18), raised by unknown_geometry_j (four levels: the
// bridge height) when flag 0x100 of +0x140 is set.
#include "shared/cell.hpp"

CoordStruct CellClass::unknown_slot22() const
{
    if (unknown_140 & 0x100) {
        return Center_Coord() + CoordStruct(0, 0, unknown_geometry_j);
    }
    return Center_Coord();
}
