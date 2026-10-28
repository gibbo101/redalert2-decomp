// ?Load@CaptureManagerClass@@UAGJPAUIStream@@@Z (0x00468280)
// AbstractClass load, vtables, pointer fixups.
#include "shared/capture_manager.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall CaptureManagerClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) CaptureManagerClass(NoInitClass());
        SwizzleManager.Swizzle((void **)&unknown_24);
        SwizzleManager.Swizzle((void **)&unknown_28);
        SwizzleManager.Swizzle((void **)&Owner);
    }
    return result;
}
