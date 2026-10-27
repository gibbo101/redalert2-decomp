// ?Load@AITriggerTypeClass@@UAGJPAUIStream@@@Z (0x0041C7B0)
// AbstractClass load, vtables, pointer fixups.
#include "shared/ai_trigger_type.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractTypeClass@@QAE@ABVNoInitClass@@@Z=004106e0
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall AITriggerTypeClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) AITriggerTypeClass(NoInitClass());
    SwizzleManager.Swizzle((void **)&unknown_d8);
    SwizzleManager.Swizzle((void **)&unknown_dc);
    SwizzleManager.Swizzle((void **)&unknown_e0);
    return S_OK;
}
