// void ObjectClass::unknown_func_5d4920(int z) (0x005D4920)
#include "shared/object_type.hpp"

void ObjectClass::unknown_func_5d4920(int z)
{
    if (unknown_74) {
        unknown_slot71(0);
        Coord.Z = z;
        unknown_slot71(1);
    } else {
        Coord.Z = z;
    }
}
