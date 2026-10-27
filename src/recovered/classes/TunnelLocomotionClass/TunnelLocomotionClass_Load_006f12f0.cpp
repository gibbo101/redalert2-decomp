// HRESULT __stdcall TunnelLocomotionClass::Load(IStream *stream) (0x006F12F0)
// LocomotionClass::Load, then rebuilt in place.
#include "shared/tunnel_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref ??_7LocomotionClass@@6BIPersistStream@@@=007a33b4
// @ref ??_7LocomotionClass@@6BILocomotion@@@=007a32ec
// @ref ??_7TunnelLocomotionClass@@6BIPersistStream@@@=007adc74
// @ref ??_7TunnelLocomotionClass@@6BILocomotion@@@=007adbac

HRESULT __stdcall TunnelLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) TunnelLocomotionClass(NoInitClass());
    }
    return result;
}
