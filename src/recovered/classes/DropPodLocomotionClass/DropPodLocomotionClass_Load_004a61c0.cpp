// HRESULT __stdcall DropPodLocomotionClass::Load(IStream *stream) (0x004A61C0)
// LocomotionClass::Load, rebuilt in place; then a flag and, when set, the
// carried locomotor (OleLoadFromStream).
#include "shared/droppod_locomotion.hpp"
// @ref ?Load@LocomotionClass@@UAGJPAUIStream@@@Z=0053d3c0
// @ref __imp__OleLoadFromStream@12=0079a5ec
// @ref _IID_ILocomotion=007a5890
// @ref ??_7DropPodLocomotionClass@@6BIPersistStream@@@=007a0958
// @ref ??_7DropPodLocomotionClass@@6BILocomotion@@@=007a0890
// @ref ??_7DropPodLocomotionClass@@6B@=007a086c

HRESULT __stdcall DropPodLocomotionClass::Load(IStream *stream)
{
    HRESULT result = LocomotionClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) DropPodLocomotionClass(NoInitClass());
        bool piggybacking;
        stream->Read(&piggybacking, sizeof(piggybacking), 0);
        if (piggybacking) {
            result = OleLoadFromStream(stream, IID_ILocomotion, (void **)&Piggybacker);
        }
    }
    return result;
}
