#define RA2_COORD_EQUAL_MEMBER
// bool CoordStruct::operator==(CoordStruct const &coord) const (0x0061A8B0)
#include "shared/planning.hpp"

bool CoordStruct::operator==(CoordStruct const &coord) const
{
    return X == coord.X && Y == coord.Y && Z == coord.Z;
}
