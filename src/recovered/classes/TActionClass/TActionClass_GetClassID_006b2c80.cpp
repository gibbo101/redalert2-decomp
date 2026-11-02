// HRESULT __stdcall TActionClass::GetClassID(GUID *clsid) (0x006B2C80)
#include "shared/object.hpp"

HRESULT __stdcall TActionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TActionClass;
    return S_OK;
}


