// long __stdcall MapClass::Is_Visible(Cell cell) (0x00547FA0, IGameMap slot 3)
// Bit 3 of the cell's flags (the dummy cell's when off the map).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

long __stdcall MapClass::Is_Visible(Cell cell)
{
    return ((*this)[Cell(cell.X, cell.Y)].unknown_12c >> 3) & 1;
}
