// ?Load@RadSiteClass@@UAGJPAUIStream@@@Z (0x00637490)
// AbstractClass load, vtables, light pointer fixup.
#include "shared/radsite.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall RadSiteClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) RadSiteClass(NoInitClass());
        SwizzleManager.Swizzle((void **)&LightSource);
    }
    return result;
}
