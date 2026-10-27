// HRESULT __stdcall JumpjetLocomotionClass::Load(IStream *stream) (0x0052FBE0)
// LocomotionClass::Load, then the vtables are restored in place.
#include "shared/jumpjet_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref ??_7JumpjetLocomotionClass@@6BIPersistStream@@@=007a536c
// @ref ??_7JumpjetLocomotionClass@@6BILocomotion@@@=007a52a4

HRESULT __stdcall JumpjetLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) JumpjetLocomotionClass(NoInitClass());
    }
    return result;
}
