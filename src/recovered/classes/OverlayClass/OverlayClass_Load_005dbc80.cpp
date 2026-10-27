// HRESULT __stdcall OverlayClass::Load(IStream *stream) (0x005DBC80)
// Restores the overlay in place and swizzles its type.
#include "shared/overlay.hpp"
// @ref ?Load@ObjectClass@@UAGJPAUIStream@@@Z=005d4760
// @ref ??0ObjectClass@@QAE@ABVNoInitClass@@@Z=005d2500
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall OverlayClass::Load(IStream *stream)
{
    HRESULT result = ObjectClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) OverlayClass(NoInitClass());
        SwizzleManager.Swizzle((void **)&Class);
    }
    return result;
}
