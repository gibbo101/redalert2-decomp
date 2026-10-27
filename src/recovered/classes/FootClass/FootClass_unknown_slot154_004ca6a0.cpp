// bool FootClass::unknown_slot154() (0x004CA6A0)
// TechnoClass's test, refused for a CloakStop type while the locomotor is
// moving (ILocomotion::Is_Moving_Now).
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_slot154@TechnoClass@@UAE_NXZ=006d6de0

bool FootClass::unknown_slot154()
{
    if (TechnoClass::unknown_slot154()) {
        if (!unknown_slot32()->CloakStop || !Locomotor.Checked()->Is_Moving_Now()) {
            return true;
        }
    }
    return false;
}
