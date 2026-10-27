// HRESULT __stdcall TeleportLocomotionClass::Load(IStream *stream) (0x006E1770)
// LocomotionClass::Load, rebuilt in place; then a flag and, when set, the
// carried locomotor (OleLoadFromStream).
#include "shared/teleport_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref __imp__OleLoadFromStream@12=0079a5ec
// @ref _IID_ILocomotion=007a5890
// @ref ??_7LocomotionClass@@6BIPersistStream@@@=007a33b4
// @ref ??_7LocomotionClass@@6BILocomotion@@@=007a32ec
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_7TeleportLocomotionClass@@6BIPersistStream@@@=007ad270
// @ref ??_7TeleportLocomotionClass@@6BILocomotion@@@=007ad1a8
// @ref ??_7TeleportLocomotionClass@@6B@=007ad184

HRESULT __stdcall TeleportLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) TeleportLocomotionClass(NoInitClass());
        bool piggybacking;
        stream->Read(&piggybacking, sizeof(piggybacking), 0);
        if (piggybacking) {
            result = OleLoadFromStream(stream, IID_ILocomotion, (void **)&Piggybacker);
        }
    }
    return result;
}
