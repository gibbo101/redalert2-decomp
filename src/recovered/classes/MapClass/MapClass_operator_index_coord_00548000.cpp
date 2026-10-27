// CellClass &MapClass::operator[](CoordStruct const &coord) (0x00548000)
// The cell under a lepton coordinate; the dummy cell (with the requested
// coordinates) when the index is outside the cell vector or the slot is empty.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

CellClass &MapClass::operator[](CoordStruct const &coord)
{
    int x = coord.X / 256;
    int y = coord.Y / 256;
    int index = (y << 9) + x;
    if (index >= 0 && index < Cells.Length() && Cells[index] != 0) {
        return *Cells[index];
    }
    unknown_dummy_cell_a6f9f8.MapCoords = Cell(x, y);
    return unknown_dummy_cell_a6f9f8;
}
