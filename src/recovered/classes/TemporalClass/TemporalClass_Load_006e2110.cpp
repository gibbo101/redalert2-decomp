// ?Load@TemporalClass@@UAGJPAUIStream@@@Z (0x006E2110)
// AbstractClass load, vtables, pointer fixups.
#include "shared/temporal.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall TemporalClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) TemporalClass(NoInitClass());
        SwizzleManager.Swizzle((void **)&Owner);
        SwizzleManager.Swizzle((void **)&Target);
        SwizzleManager.Swizzle((void **)&unknown_40);
        SwizzleManager.Swizzle((void **)&unknown_44);
        SwizzleManager.Swizzle((void **)&unknown_38);
        SwizzleManager.Swizzle((void **)&unknown_3c);
    }
    return result;
}
