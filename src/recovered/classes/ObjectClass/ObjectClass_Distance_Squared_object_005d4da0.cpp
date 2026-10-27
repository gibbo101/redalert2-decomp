// int ObjectClass::Distance_Squared(ObjectClass const *other) const (0x005D4DA0)
#include "shared/object_type.hpp"

int ObjectClass::Distance_Squared(ObjectClass const *other) const
{
    if (other == 0) {
        return 0;
    }
    CoordStruct here = Center_Coord();
    CoordStruct there = other->Center_Coord();
    int dx = here.X - there.X;
    int dy = here.Y - there.Y;
    return dy * dy + dx * dx;
}
