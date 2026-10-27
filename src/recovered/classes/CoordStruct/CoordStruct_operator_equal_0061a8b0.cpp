#define RA2_COORD_EQUAL_MEMBER
// int CoordStruct::operator==(CoordStruct const &coord) const (0x0061A8B0)
#include "shared/planning.hpp"

int CoordStruct::operator==(CoordStruct const &coord) const
{
    if (X == coord.X && Y == coord.Y && Z == coord.Z) {
        return 1;
    }
    return 0;
}
