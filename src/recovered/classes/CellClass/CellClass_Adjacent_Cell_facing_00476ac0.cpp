// CellClass &CellClass::Adjacent_Cell(unsigned facing) (0x00476AC0): the
// neighbouring map cell toward facing; this cell for facings past 7.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"

CellClass &CellClass::Adjacent_Cell(unsigned facing)
{
    if (facing >= 8) {
        return *this;
    }
    Cell cell = MapCoords;
    return Map[Adjacent_Cell(cell, facing)];
}
