// bool HouseClass::Is_Ally(HouseClass const *house) const (0x004E5540)
#include "shared/techno.hpp"

bool HouseClass::Is_Ally(HouseClass const *house) const
{
    if (house != 0) {
        if (house == this) {
            return true;
        }
        return Is_Ally(house->ArrayIndex);
    }
    return false;
}
