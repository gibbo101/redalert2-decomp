// bool HouseClass::Is_Ally(TechnoClass const *techno) const (0x004E5580)
#include "shared/techno.hpp"

bool HouseClass::Is_Ally(TechnoClass const *techno) const
{
    if (techno != 0) {
        HouseClass *house = techno->Owning_House();
        if (house != 0) {
            if (house == this) {
                return true;
            }
            return Is_Ally(house->ArrayIndex);
        }
    }
    return false;
}
