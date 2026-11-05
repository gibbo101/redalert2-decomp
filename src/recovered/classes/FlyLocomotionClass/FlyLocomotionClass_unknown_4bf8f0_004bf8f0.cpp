// bool FlyLocomotionClass::unknown_4bf8f0() (0x004BF8F0; TibSun Needs_To_Land)
#include "shared/fly_locomotion.hpp"
#include "shared/aircraft.hpp"
bool FlyLocomotionClass::unknown_4bf8f0()
{
    FootClass *object = LinkedTo;
    if (object && object->Kind_Of() == 2 && ((IFlyControl *)(AircraftClass *)object)->Is_Locked()) {
        return false;
    }
    if (unknown_51) {
        return true;
    }
    if (!unknown_5c) {
        return true;
    }
    UnknownHeldComPtr<IFlyControl, &unknown_uuid_7d80a8> flyctrl(LinkedTo);
    if (flyctrl != 0 && !flyctrl->Is_Strafe() && !flyctrl.Checked()->Is_Fighter()) {
        return true;
    }
    if (LinkedTo->unknown_254 == 0) {
        return true;
    }
    return false;
}
