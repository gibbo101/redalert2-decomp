// The complete real out-of-line operator+ copy at0069ECF0.
// This guard is used only by this provider; every caller retains the normal inline body.
#define RA2_COORD_PLUS_SOURCE
#include "shared/coord.hpp"
CoordStruct CoordStruct::operator+(CoordStruct const &coord) const
{
    return CoordStruct(X+coord.X,Y+coord.Y,Z+coord.Z);
}
