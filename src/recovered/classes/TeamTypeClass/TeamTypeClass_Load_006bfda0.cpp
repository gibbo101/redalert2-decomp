// HRESULT __stdcall TeamTypeClass::Load(IStream *stream) (0x006BFDA0)
// Restores the type in place and swizzles its owner, tag, script and task
// force.
#include "shared/team_type.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractTypeClass@@QAE@ABVNoInitClass@@@Z=004106e0
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall TeamTypeClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) TeamTypeClass(NoInitClass());
        SwizzleManager.Swizzle((void **)&Owner);
        SwizzleManager.Swizzle((void **)&Tag);
        SwizzleManager.Swizzle((void **)&Script);
        SwizzleManager.Swizzle((void **)&TaskForce);
        result = S_OK;
    }
    return result;
}
