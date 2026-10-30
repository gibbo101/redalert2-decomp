// int __fastcall Unknown_004763D0(CoordStruct const &coord) (0x004763D0)
// Westwood's CellClass::Spot_Index: the sub-cell spot of a coordinate. 0 near
// the centre of the cell (closer than 60 leptons to (0x80, 0x80)), otherwise
// 1 plus a bit for each of X and Y past the centre (InfantryClass, DisplayClass
// 0x0049CBF0, JumpjetLocomotionClass). Declared in shared/infantry.hpp.
#include "shared/cell.hpp"
#include "shared/fast_math.hpp"

int __fastcall Unknown_004763D0(CoordStruct const &coord)
{
    int x = coord.X & 0xff;
    int y = coord.Y & 0xff;
    Point2D rel(x - 0x80, y - 0x80);
    int distance = (int)Fast_Sqrt((double)rel.X * rel.X + (double)rel.Y * rel.Y);
    if (distance < 60) {
        return 0;
    }
    int index = 0;
    if (x > 0x80) {
        index = 1;
    }
    if (y > 0x80) {
        index |= 2;
    }
    if (index == 0) {
        return 0;
    }
    return index + 1;
}
