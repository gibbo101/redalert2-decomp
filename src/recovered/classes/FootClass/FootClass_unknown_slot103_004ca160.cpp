// void FootClass::unknown_slot103(CoordStruct const &coord) (0x004CA160)
// ObjectClass's slot 103, bracketed by slot 71 (false, then true) while
// the object is on the map (+0x74).
#include "shared/foot.hpp"
// @ref ?unknown_slot103@ObjectClass@@UAEXABUCoordStruct@@@Z=005d51c0

void FootClass::unknown_slot103(CoordStruct const &coord)
{
    if (unknown_74) {
        unknown_slot71(0);
        ObjectClass::unknown_slot103(coord);
        unknown_slot71(1);
    } else {
        ObjectClass::unknown_slot103(coord);
    }
}
