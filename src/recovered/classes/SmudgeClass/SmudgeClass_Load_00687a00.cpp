// HRESULT __stdcall SmudgeClass::Load(IStream *stream) (0x00687A00)
// Restores the smudge in place and swizzles its type.
#include "shared/smudge.hpp"
// @ref ?Load@ObjectClass@@UAGJPAUIStream@@@Z=005d4760
// @ref ??0ObjectClass@@QAE@ABVNoInitClass@@@Z=005d2500
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall SmudgeClass::Load(IStream *stream)
{
    HRESULT result = ObjectClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) SmudgeClass(NoInitClass());
        SwizzleManager.Swizzle((void **)&Class);
    }
    return result;
}
