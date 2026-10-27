// HRESULT __stdcall ShipLocomotionClass::Load(IStream *stream) (0x00675840)
// LocomotionClass::Load, rebuilt in place; then a flag and, when set, the
// carried locomotor (OleLoadFromStream).
#include "shared/ship_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref __imp__OleLoadFromStream@12=0079a5ec
// @ref _IID_ILocomotion=007a5890
// @ref ??_7ShipLocomotionClass@@6BIPersistStream@@@=007ab204
// @ref ??_7ShipLocomotionClass@@6BILocomotion@@@=007ab13c
// @ref ??_7ShipLocomotionClass@@6B@=007ab118

HRESULT __stdcall ShipLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) ShipLocomotionClass(NoInitClass());
        bool piggybacking;
        stream->Read(&piggybacking, sizeof(piggybacking), 0);
        if (piggybacking) {
            result = OleLoadFromStream(stream, IID_ILocomotion, (void **)&Piggybacker);
        }
    }
    return result;
}
