// HRESULT __stdcall RocketLocomotionClass::Load(IStream *stream) (0x0063EBA0)
// LocomotionClass::Load, then rebuilt in place (restarting the second timer).
#include "shared/rocket_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_7LocomotionClass@@6BIPersistStream@@@=007a33b4
// @ref ??_7LocomotionClass@@6BILocomotion@@@=007a32ec
// @ref ??_7RocketLocomotionClass@@6BIPersistStream@@@=007a8fa4
// @ref ??_7RocketLocomotionClass@@6BILocomotion@@@=007a8edc

HRESULT __stdcall RocketLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) RocketLocomotionClass(NoInitClass());
    }
    return result;
}
