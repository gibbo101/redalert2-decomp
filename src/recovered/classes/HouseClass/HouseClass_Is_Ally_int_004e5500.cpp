// bool HouseClass::Is_Ally(int house) const (0x004E5500)
#include "shared/techno.hpp"

bool HouseClass::Is_Ally(int house) const
{
    if (house == ArrayIndex) {
        return true;
    }
    if (house != -1) {
        return (Allies & (1 << house)) != 0;
    }
    return false;
}
