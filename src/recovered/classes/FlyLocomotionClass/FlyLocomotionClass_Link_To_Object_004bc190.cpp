// HRESULT __stdcall FlyLocomotionClass::Link_To_Object(void *object) (0x004BC190, ILocomotion 3)
// Links, then notes whether the object is an airport-bound aircraft.
#include "shared/fly_locomotion.hpp"
// @ref ?Link_To_Object@LocomotionClass@@UAGJPAX@Z=0053d010

HRESULT __stdcall FlyLocomotionClass::Link_To_Object(void *object)
{
    HRESULT result = LocomotionClass::Link_To_Object(object);
    if (result == S_OK) {
        if (object && ((FootClass *)object)->Kind_Of() == 2
            && ((UnknownFlyAircraft *)object)->Type->AirportBound) {
            unknown_18 = true;
        } else {
            unknown_18 = false;
        }
    }
    return result;
}
