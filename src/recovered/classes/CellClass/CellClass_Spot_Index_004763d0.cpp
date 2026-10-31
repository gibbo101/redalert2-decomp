// int __fastcall Unknown_004763D0(CoordStruct const &coord) (0x004763D0)
// Westwood's CellClass::Spot_Index: the sub-cell spot of a coordinate. 0 near
// the centre of the cell (closer than 60 leptons to (0x80, 0x80)), otherwise
// 1 plus a bit for each of X and Y past the centre (InfantryClass, DisplayClass
// 0x0049CBF0, JumpjetLocomotionClass). Declared in shared/infantry.hpp.
#include "shared/cell.hpp"


// The distance between two points (Westwood's Distance(Point2D, Point2D); Closest_Free_Spot
// 0x004764B0 expands Spot_Index with Length 0x0047D060 out of line).
inline int Distance(Point2D const &point1, Point2D const &point2)
{
    return (point1 - point2).Length();
}

int __fastcall Unknown_004763D0(CoordStruct const &coord)
{
    int x = coord.X & 0xff;
    int y = coord.Y & 0xff;
    Point2D rel(x, y);
    if (Distance(rel, Point2D(0x80, 0x80)) < 60) {
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
