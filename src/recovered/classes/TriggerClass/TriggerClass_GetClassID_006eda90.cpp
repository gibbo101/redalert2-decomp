// HRESULT __stdcall TriggerClass::GetClassID(GUID *clsid) (0x006EDA90)
#include "shared/object.hpp"

HRESULT __stdcall TriggerClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TriggerClass;
    return S_OK;
}
