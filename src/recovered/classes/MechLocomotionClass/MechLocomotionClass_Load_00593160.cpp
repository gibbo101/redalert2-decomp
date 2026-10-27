// HRESULT __stdcall MechLocomotionClass::Load(IStream *stream) (0x00593160)
// LocomotionClass::Load, then rebuilt in place.
#include "shared/mech_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref ??_7MechLocomotionClass@@6BIPersistStream@@@=007a6174
// @ref ??_7MechLocomotionClass@@6BILocomotion@@@=007a60ac

HRESULT __stdcall MechLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) MechLocomotionClass(NoInitClass());
    }
    return result;
}
