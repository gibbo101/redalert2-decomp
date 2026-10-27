// HRESULT __stdcall FlyLocomotionClass::Load(IStream *stream) (0x004BF440)
// LocomotionClass::Load, then rebuilt in place.
#include "shared/fly_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref ??_7FlyLocomotionClass@@6BIPersistStream@@@=007a10cc
// @ref ??_7FlyLocomotionClass@@6BILocomotion@@@=007a1004

HRESULT __stdcall FlyLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) FlyLocomotionClass(NoInitClass());
    }
    return result;
}
