// HRESULT __stdcall DriveLocomotionClass::Load(IStream *stream) (0x0049F880)
// LocomotionClass::Load, rebuilt in place; then a flag and, when set, the
// carried locomotor (OleLoadFromStream).
#include "shared/drive_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref __imp__OleLoadFromStream@12=0079a5ec
// @ref _IID_ILocomotion=007a5890
// @ref ??_7DriveLocomotionClass@@6BIPersistStream@@@=007a0594
// @ref ??_7DriveLocomotionClass@@6BILocomotion@@@=007a04cc
// @ref ??_7DriveLocomotionClass@@6B@=007a04a8

HRESULT __stdcall DriveLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) DriveLocomotionClass(NoInitClass());
        bool piggybacking;
        stream->Read(&piggybacking, sizeof(piggybacking), 0);
        if (piggybacking) {
            result = OleLoadFromStream(stream, IID_ILocomotion, (void **)&Piggybacker);
        }
    }
    return result;
}
