// bool HouseClass::Is_Ally(ObjectClass const *object) const (0x004E55E0)
#include "shared/techno.hpp"

bool HouseClass::Is_Ally(ObjectClass const *object) const
{
    if (object != 0 && object->AbstractFlags.IsObject) {
        HouseClass *house = object->Owning_House();
        if (house != 0) {
            if (house == this) {
                return true;
            }
            return Is_Ally(house->ArrayIndex);
        }
    }
    return false;
}
