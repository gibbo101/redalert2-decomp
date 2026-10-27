// CellClass &MapClass::operator[](Cell const &cell) (0x00548070)
// The cell at cell; the dummy cell (with the requested coordinates) outside
// the 512 x 512 index range or for an empty slot.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

CellClass &MapClass::operator[](Cell const &cell)
{
    int index = (cell.Y << 9) + cell.X;
    if (index >= 0 && index < 0x40000 && Cells[index] != 0) {
        return *Cells[index];
    }
    unknown_dummy_cell_a6f9f8.MapCoords = cell;
    return unknown_dummy_cell_a6f9f8;
}
