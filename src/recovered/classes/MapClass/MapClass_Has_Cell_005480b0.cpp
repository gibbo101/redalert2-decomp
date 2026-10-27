// bool MapClass::Has_Cell(Cell const &cell) (0x005480B0)
// Whether the cell vector holds a cell at cell (no range check).
#include "shared/map.hpp"

bool MapClass::Has_Cell(Cell const &cell)
{
    return Cells[(cell.Y << 9) + cell.X] ? true : false;
}
