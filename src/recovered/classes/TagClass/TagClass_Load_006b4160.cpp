// HRESULT __stdcall TagClass::Load(IStream *stream) (0x006B4160)
#include "shared/object.hpp"

HRESULT __stdcall TagClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) TagClass(NoInitClass());
    SwizzleManager.Swizzle((void **)&Class);
    SwizzleManager.Swizzle((void **)&AttachedTrigger);
    return S_OK;
}
