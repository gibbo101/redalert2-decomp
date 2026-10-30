// Coordinate difference, original004348F0:47body bytes plus1NOP to00434920.
// Same shared operation and signature as the inline header definition.
#define RA2_COORD_MINUS_SOURCE
#include "shared/coord.hpp"

CoordStruct CoordStruct::operator-(CoordStruct const &coord) const
{
    return CoordStruct(X-coord.X,Y-coord.Y,Z-coord.Z);
}
