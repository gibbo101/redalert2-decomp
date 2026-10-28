// CoordStruct UnitTypeClass::unknown_slot30() const (0x0070AAB0)
// Three quarters of +0x1BC in each dimension, at most 60.
#include "shared/unit_type.hpp"

#define Min(a, b) ((a) < (b) ? (a) : (b))

CoordStruct UnitTypeClass::unknown_slot30() const
{
    int width = unknown_1bc - unknown_1bc / 4;
    if (width >= 60) {
        width = 60;
    }
    return CoordStruct(width, width, Min(unknown_1bc - unknown_1bc / 4, 60));
}
