// HRESULT __stdcall TagTypeClass::Load(IStream *stream) (0x006B4E20)
#include "shared/object.hpp"

HRESULT __stdcall TagTypeClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) TagTypeClass(NoInitClass());
    SwizzleManager.Swizzle((void **)&Triggers);
    return S_OK;
}
