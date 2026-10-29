// Cell HouseClass::Zone_Cell(int zone) const (0x004EAF30)
// The cell at the centre of a base zone (RA's Zone_Cell): the base centre
// for zone 0, else three radii (+0x53C8) from it to the north (1), east (2),
// south (3) or west (4); unknown_cell_a40f10 for any other zone.
#include "shared/techno.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_vector3.hpp"
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
// @ref ??0UnknownVector3@@QAE@HHH@Z=0041b630

// A coordinate moved a distance along a direction (raw 16-bit, 0 north,
// clockwise; folded to its angle in radians).
inline UnknownVector3 Zone_Coord_Move(CoordStruct const &coord, short dir, int distance)
{
    double radians = (dir - 0x3FFF) * -(2 * 3.141592653589793 / 65534);
    int x, y, z;
    z = coord.Z;
    y = (int)(coord.Y - (double)Fast_Sin(radians) * distance);
    x = (int)(coord.X + (double)Fast_Cos(radians) * distance);
    UnknownVector3 result(x, y, z);
    return result;
}

Cell HouseClass::Zone_Cell(int zone) const
{
    switch (zone) {
    case 0:
        return Coord_Cell(BaseCenter);
    case 1: {
        UnknownVector3 coord = Zone_Coord_Move(BaseCenter, (short)0x0000, unknown_53c8 * 3);
        return Coord_Cell(CoordStruct(coord.X, coord.Y, coord.Z));
    }
    case 2: {
        UnknownVector3 coord = Zone_Coord_Move(BaseCenter, (short)0x4000, unknown_53c8 * 3);
        return Coord_Cell(CoordStruct(coord.X, coord.Y, coord.Z));
    }
    case 4: {
        UnknownVector3 coord = Zone_Coord_Move(BaseCenter, (short)0xC000, unknown_53c8 * 3);
        return Coord_Cell(CoordStruct(coord.X, coord.Y, coord.Z));
    }
    case 3: {
        UnknownVector3 coord = Zone_Coord_Move(BaseCenter, (short)0x8000, unknown_53c8 * 3);
        return Coord_Cell(CoordStruct(coord.X, coord.Y, coord.Z));
    }
    }
    return unknown_cell_a40f10;
}
