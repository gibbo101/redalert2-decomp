// void TubeClass::Add_Direction(int facing) (0x006EF7D0)
// Extends the tube by one step (TibSun Add_Direction): the facing is appended to the
// directions while fewer than 99 are held, and the exit cell moves toward it.
#include "shared/tube.hpp"
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70

#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
#include "shared/adjacent_cell.hpp"
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    return cell + AdjacentCell[facing & 7];
}
#endif

void TubeClass::Add_Direction(int facing)
{
    if (unknown_1c0 < 99) {
        Directions[unknown_1c0] = facing;
        Directions[++unknown_1c0] = -1;
    }
    ExitCell = Adjacent_Cell(ExitCell, facing);
}
