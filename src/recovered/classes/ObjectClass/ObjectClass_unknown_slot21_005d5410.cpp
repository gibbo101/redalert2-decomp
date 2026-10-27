// bool ObjectClass::unknown_slot21() const (0x005D5410)
#include "shared/object_type.hpp"

bool ObjectClass::unknown_slot21() const
{
    if (unknown_74 && unknown_slot108() >= unknown_geometry_g * 2) {
        return true;
    }
    return false;
}
