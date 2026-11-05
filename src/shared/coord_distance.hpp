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
#ifdef RA2_RADSITE_COORD_DISTANCE_DIFFERENCE
    CoordStruct d = a - b;
#else
    CoordStruct d(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
#endif
    return (int)unknown_sqrt_4ba410((double)d.X * d.X + (double)d.Z * d.Z + (double)d.Y * d.Y);
}

// The length of a cell offset (both slot 42s, MultiplayerGameMode 0x005B7920 and MPCooperative
// 0x005A3F90, sum it over the taken start cells).
inline double Cell_Distance(double x, double y)
{
    return unknown_sqrt_4ba410(x * x + y * y);
}

#endif
