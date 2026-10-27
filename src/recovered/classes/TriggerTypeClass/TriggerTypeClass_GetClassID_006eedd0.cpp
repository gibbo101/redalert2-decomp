// HRESULT __stdcall TriggerTypeClass::GetClassID(GUID *clsid) (0x006EEDD0)
#include "shared/object.hpp"

HRESULT __stdcall TriggerTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TriggerTypeClass;
    return S_OK;
}
