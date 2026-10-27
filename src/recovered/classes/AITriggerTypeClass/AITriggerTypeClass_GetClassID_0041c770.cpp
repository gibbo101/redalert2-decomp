// ?GetClassID@AITriggerTypeClass@@UAGJPAUGUID@@@Z (0x0041C770)
// The class identifier.
#include "shared/ai_trigger_type.hpp"
// @ref _CLSID_AITriggerTypeClass=007a1ea0

HRESULT __stdcall AITriggerTypeClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_AITriggerTypeClass;
    return S_OK;
}
