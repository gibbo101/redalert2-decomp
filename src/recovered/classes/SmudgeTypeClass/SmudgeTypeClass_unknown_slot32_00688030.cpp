// bool SmudgeTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const (0x00688030)
// Creates a smudge of this type at the centre of the cell (no house).
#include "shared/smudge_type.hpp"
#include "shared/smudge.hpp"
// @ref ??2@YAPAXI@Z=00782017

bool SmudgeTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const
{
    if (new SmudgeClass((SmudgeTypeClass *)this, CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0), -1) != 0) {
        return true;
    }
    return false;
}
