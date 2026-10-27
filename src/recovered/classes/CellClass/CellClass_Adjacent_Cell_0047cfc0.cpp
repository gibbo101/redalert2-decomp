// Cell __fastcall CellClass::Adjacent_Cell(Cell const &cell, int facing)
// (0x0047CFC0): the cell next to cell toward an 8-way facing.
#include "shared/cell.hpp"

Cell __fastcall CellClass::Adjacent_Cell(Cell const &cell, int facing)
{
    return cell + AdjacentCell[facing & 7];
}
