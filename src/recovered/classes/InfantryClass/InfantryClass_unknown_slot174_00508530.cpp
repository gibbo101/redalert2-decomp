// int InfantryClass::unknown_slot174(AbstractClass *target) (0x00508530, slot 174)
// During the deploy sequences (27-30), the type's DeployFireWeapon when DeployFire
// is set; otherwise TechnoClass's.
#include "shared/infantry.hpp"
// @ref ?unknown_slot174@TechnoClass@@UAEHPAVAbstractClass@@@Z=006c1380

int InfantryClass::unknown_slot174(AbstractClass *target)
{
    if ((Sequence == 27 || Sequence == 28 || Sequence == 29 || Sequence == 30) && Type->DeployFire) {
        return Type->DeployFireWeapon;
    }
    return TechnoClass::unknown_slot174(target);
}
