// HRESULT __stdcall TriggerTypeClass::Load(IStream *stream) (0x006EEE10)
#include "shared/object.hpp"

HRESULT __stdcall TriggerTypeClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) TriggerTypeClass(NoInitClass());
    SwizzleManager.Swizzle((void **)&Next);
    SwizzleManager.Swizzle((void **)&Events);
    SwizzleManager.Swizzle((void **)&Actions);
    SwizzleManager.Swizzle((void **)&unknown_a4);
    return S_OK;
}
