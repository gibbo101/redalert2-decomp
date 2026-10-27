// HRESULT __stdcall TEventClass::GetClassID(GUID *clsid) (0x006E6C20)
#include "shared/object.hpp"

HRESULT __stdcall TEventClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TEventClass;
    return S_OK;
}
