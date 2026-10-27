// HRESULT __stdcall TActionClass::Load(IStream *stream) (0x006B2CC0)
#include "shared/object.hpp"

HRESULT __stdcall TActionClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) TActionClass(NoInitClass());
    SwizzleManager.Swizzle((void **)&Next);
    SwizzleManager.Swizzle((void **)&unknown_30);
    SwizzleManager.Swizzle((void **)&unknown_4c);
    SwizzleManager.Swizzle((void **)&unknown_50);
    return S_OK;
}
