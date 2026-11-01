#define RA2_RECT_POINT_INLINE
// ObjectClass slot43/00423D50;existing CoordStruct sum body.
#include "shared/object.hpp"

CoordStruct ObjectClass::unknown_slot43(int unknown)
{
    return Center_Coord() + CoordStruct(0, 0, 50);
}
