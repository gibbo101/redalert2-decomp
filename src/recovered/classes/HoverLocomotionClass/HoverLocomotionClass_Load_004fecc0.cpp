// HRESULT __stdcall HoverLocomotionClass::Load(IStream *stream) (0x004FECC0)
// LocomotionClass::Load, then rebuilt in place.
#include "shared/hover_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref ??_7LocomotionClass@@6BIPersistStream@@@=007a33b4
// @ref ??_7LocomotionClass@@6BILocomotion@@@=007a32ec
// @ref ??0FacingClass@@QAE@XZ=004b89d0
// @ref ??_7HoverLocomotionClass@@6BIPersistStream@@@=007a32b4
// @ref ??_7HoverLocomotionClass@@6BILocomotion@@@=007a31ec

HRESULT __stdcall HoverLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) HoverLocomotionClass(NoInitClass());
    }
    return result;
}
