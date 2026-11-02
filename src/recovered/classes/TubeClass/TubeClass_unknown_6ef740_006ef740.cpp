// bool TubeClass::unknown_6ef740(Cell const &cell) const (0x006EF740)
// TibSun Not_In_Tube: false when the cell lies on the tube's path after its entry cell
// (the entry cell itself gives true).
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

bool TubeClass::unknown_6ef740(Cell const &cell) const
{
    Cell tubecell = EnterCell;
    if (tubecell == cell) {
        return true;
    }
    int dir = 0;
    while (Directions[dir] != -1) {
        tubecell = Adjacent_Cell(tubecell, Directions[dir++]);
        if (tubecell == cell) {
            return false;
        }
    }
    return true;
}
