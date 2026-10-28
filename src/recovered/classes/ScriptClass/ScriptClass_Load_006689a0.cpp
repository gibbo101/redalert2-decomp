// HRESULT __stdcall ScriptClass::Load(IStream *stream) (0x006689A0)
// Restores the script in place and swizzles its type.
#include "shared/script.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall ScriptClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) ScriptClass(NoInitClass());
        SwizzleManager.Swizzle((void **)&Class);
        result = S_OK;
    }
    return result;
}

