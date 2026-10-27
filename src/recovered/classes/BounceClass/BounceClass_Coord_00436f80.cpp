// CoordStruct BounceClass::Coord() const -- 0x00436F80
// The bouncing object's float position (+0x18) truncated to a coordinate.
#include "shared/bounce.hpp"
// @ref __ftol=0077f110

CoordStruct BounceClass::Coord() const
{
    return CoordStruct((int)unknown_00.Position.X, (int)unknown_00.Position.Y, (int)unknown_00.Position.Z);
}
