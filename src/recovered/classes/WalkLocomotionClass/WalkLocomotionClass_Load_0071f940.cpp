// HRESULT __stdcall WalkLocomotionClass::Load(IStream *stream) (0x0071F940)
// LocomotionClass::Load, rebuilt in place; then a flag and, when set, the
// carried locomotor (OleLoadFromStream).
#include "shared/walk_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref __imp__OleLoadFromStream@12=0079a5ec
// @ref _IID_ILocomotion=007a5890
// @ref ??_7WalkLocomotionClass@@6BIPersistStream@@@=007aeba0
// @ref ??_7WalkLocomotionClass@@6BILocomotion@@@=007aead8
// @ref ??_7WalkLocomotionClass@@6B@=007aeab4

HRESULT __stdcall WalkLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) WalkLocomotionClass(NoInitClass());
        bool piggybacking;
        stream->Read(&piggybacking, sizeof(piggybacking), 0);
        if (piggybacking) {
            result = OleLoadFromStream(stream, IID_ILocomotion, (void **)&Piggybacker);
        }
    }
    return result;
}
