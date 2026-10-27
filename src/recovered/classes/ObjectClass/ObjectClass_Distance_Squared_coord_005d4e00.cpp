// int ObjectClass::Distance_Squared(CoordStruct const &coord) const (0x005D4E00)
#include "shared/object_type.hpp"

int ObjectClass::Distance_Squared(CoordStruct const &coord) const
{
    CoordStruct here = Center_Coord();
    int dx = here.X - coord.X;
    int dy = here.Y - coord.Y;
    return dy * dy + dx * dx;
}
