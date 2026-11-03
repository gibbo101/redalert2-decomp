// BuildingClass (shared/building_class.hpp) with shared/building_type.hpp's
// file-local rect, as Building.CPP and the other users of this header see it.
#ifndef RA2_BUILDING_HPP
#define RA2_BUILDING_HPP

#include "shared/unknown_globals.hpp"
#define RA2_BUILDING_FULL
#include "shared/techno.hpp"
#include "shared/building_type.hpp"
#include "shared/building_class.hpp"

#ifdef RA2_BUILDING_DELAY_POINT
// Convert the pending three-field value into a coordinate at the call boundary.
inline CoordStruct::CoordStruct(TPoint3D<int> const &point)
{
    X = point.X;
    Y = point.Y;
    Z = point.Z;
}
#endif

#endif
