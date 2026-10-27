// bool FootClass::unknown_slot169(AbstractClass *target) (0x004CA350)
// Slot 171 for the centre of the cell holding the target's coordinate
// (its slot 19 as seen from this object).
#include "shared/foot.hpp"

bool FootClass::unknown_slot169(AbstractClass *target)
{
    Cell cell = Coord_Cell(target->unknown_slot19(this));
    CoordStruct center(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
    return unknown_slot171(center);
}
