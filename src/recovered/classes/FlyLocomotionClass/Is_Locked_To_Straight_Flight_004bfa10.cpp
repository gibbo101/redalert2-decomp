// @ref ?Release_Held@?$UnknownComPtr@UIFlyControl@@$1?unknown_uuid_7d80a8@@3UGUID@@B@@QAEXXZ=004bfbc0
#include "shared/fly_locomotion.hpp"
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
bool FlyLocomotionClass::Is_Locked_To_Straight_Flight_004bfa10()
{
    if (unknown_1c.Z > Map.Unknown_0055A280(unknown_1c) + 120)
        return true;
    if (LinkedTo->unknown_228 != 0 && LinkedTo->unknown_254 != 0)
        return true;
    UnknownHeldComPtr<IFlyControl, &unknown_uuid_7d80a8> flyctrl(LinkedTo);
    if (flyctrl) {
        if (flyctrl->Is_Locked())
            return true;
    }
    return false;
}
