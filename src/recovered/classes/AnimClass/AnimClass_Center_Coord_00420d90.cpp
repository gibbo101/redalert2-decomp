// CoordStruct AnimClass::Center_Coord() const (0x00420D90)
// An attached animation is placed relative to its object's center.
#include "shared/anim.hpp"

CoordStruct AnimClass::Center_Coord() const
{
    if (unknown_b4 != 0) {
        return unknown_b4->Center_Coord() + ObjectClass::Center_Coord();
    }
    return ObjectClass::Center_Coord();
}
