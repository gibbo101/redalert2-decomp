// int AnimClass::unknown_slot110() const (0x004230E0)
// The height: the coordinate's Z, plus the attached object's Z.
#include "shared/anim.hpp"

int AnimClass::unknown_slot110() const
{
    CoordStruct coord = Coord;
    if (unknown_b4 != 0) {
        int z = coord.Z;
        coord = unknown_b4->Coord;
        return z + coord.Z;
    }
    return coord.Z;
}
