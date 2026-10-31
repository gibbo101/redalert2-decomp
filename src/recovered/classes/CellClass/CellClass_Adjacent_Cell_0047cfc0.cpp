// Cell __fastcall CellClass::Adjacent_Cell(Cell const &cell, int facing)
// (0x0047CFC0): the cell next to cell toward an 8-way facing. The sum is the Cell member whose
// out-of-line copy is 0x0042ADD0: its inline expansions in the unit match 0x0047BFA0, and the
// Is_Near_Tunnel functions call 0x0042ADD0 where the budget runs out.
#include "shared/cell.hpp"

Cell __fastcall CellClass::Adjacent_Cell(Cell const &cell, int facing)
{
    return cell.unknown_42add0(AdjacentCell[facing & 7]);
}
