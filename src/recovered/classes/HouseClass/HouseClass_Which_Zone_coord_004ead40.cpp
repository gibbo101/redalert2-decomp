// int HouseClass::Which_Zone(CoordStruct const &coord) const (0x004EAD40)
// The base zone of a coordinate (RA's Which_Zone): -1 for no coordinate or
// beyond four radii of the base centre, 0 within the radius (+0x53C8), else
// by the direction from the centre (1-4; the compares are the original's).
#include "shared/techno.hpp"
#include "shared/coord_distance.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/facing.hpp"
#include "shared/fast_math.hpp"
// The direction from one coordinate to another, the X values read into
// locals (hypothesis: Westwood's Direction; Which_Zone expands it).
inline UnknownFacingDir Coord_Direction(CoordStruct const &from, CoordStruct const &to)
{
    int from_x = from.X;
    int to_x = to.X;
    return UnknownFacingDir((unsigned short)((Fast_Atan2((double)from.Y - to.Y, (double)to_x - from_x)
        - 1.5707963267948966) * -10430.060040584269));
}
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410

int HouseClass::Which_Zone(CoordStruct const &coord) const
{
    if (coord == unknown_geometry_l) {
        return -1;
    }
    int distance = Coord_Distance(BaseCenter, coord);
    if (distance <= unknown_53c8) {
        return 0;
    }
    if (distance > unknown_53c8 * 4) {
        return -1;
    }
    int facing = Dir_To_256(Coord_Direction(BaseCenter, coord));
    if (facing > 0x20 && facing < 0xE0) {
        return 1;
    }
    if (facing > 0xA0 && facing < 0x60) {
        return 3;
    }
    if (facing <= 0x20 && facing < 0x60) {
        return 2;
    }
    return 4;
}
