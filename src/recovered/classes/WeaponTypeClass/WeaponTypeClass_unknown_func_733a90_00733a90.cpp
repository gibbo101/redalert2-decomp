// bool WeaponTypeClass::unknown_func_733a90() const (0x00733A90)
#include "shared/weapon_type.hpp"

bool WeaponTypeClass::unknown_func_733a90() const
{
    if (Warhead && Warhead->Wall) {
        return true;
    }
    return false;
}
