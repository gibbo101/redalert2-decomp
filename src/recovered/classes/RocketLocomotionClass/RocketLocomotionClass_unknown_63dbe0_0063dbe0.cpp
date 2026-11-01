// CoordStruct RocketLocomotionClass::unknown_63dbe0(int distance) (0x0063DBE0)
// The point `distance` leptons ahead of the rocket along its facing and
// pitch (+0x50): Westwood's Move_Coord by the ground part of the distance,
// raised by the vertical part.
#include "shared/rocket_locomotion.hpp"
#include "shared/fast_math.hpp"
#include "shared/facing.hpp"

// Westwood's Move_Coord (TibSun inline.h): a coordinate moved along a direction.
static inline CoordStruct Move_Coord(CoordStruct const &start, UnknownFacingDir const &dir, int distance)
{
    double radians = ((short)dir.Raw - 0x3fff) * -9.587672516830327e-05;
    return CoordStruct(start.X + Fast_Cos(radians) * (double)distance, start.Y - Fast_Sin(radians) * (double)distance, start.Z);
}

CoordStruct RocketLocomotionClass::unknown_63dbe0(int distance)
{
    CoordStruct coord = Object_Coord(LinkedTo);
    CoordStruct result = Move_Coord(coord, LinkedTo->unknown_2e0.Current(), Fast_Cos(unknown_50) * (double)distance);
    result.Z += Fast_Sin(unknown_50) * (double)distance;
    return result;
}
