// bool HouseClass::Is_Ally(TechnoClass const *techno) const (0x004E5580)
#include "shared/techno.hpp"

bool HouseClass::Is_Ally(TechnoClass const *techno) const
{
    if (techno != 0) {
        return Is_Ally(techno->Owning_House());
    }
    return false;
}
