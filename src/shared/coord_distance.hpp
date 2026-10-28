// The distance between two coordinates (an inline helper, moved from
// shared/building_class.hpp; hypothesis: Westwood's Distance()). BuildingClass
// slot 281 and Receive_Message, UnitClass 0x00707170 and
// RadSiteClass::Get_Rad_Level_At 0x006379B0 expand it.
#ifndef RA2_SHARED_COORD_DISTANCE_HPP
#define RA2_SHARED_COORD_DISTANCE_HPP

#include "shared/coord.hpp"

double __cdecl unknown_sqrt_4ba410(double value);     // 0x004BA410 (shared/unknown_geometry.hpp)
inline int Coord_Distance(CoordStruct const &a, CoordStruct const &b)
{
    CoordStruct d(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
    return (int)unknown_sqrt_4ba410((double)d.X * d.X + (double)d.Z * d.Z + (double)d.Y * d.Y);
}

#endif
