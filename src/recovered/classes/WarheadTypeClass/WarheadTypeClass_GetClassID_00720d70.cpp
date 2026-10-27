// HRESULT __stdcall WarheadTypeClass::GetClassID(GUID *clsid) (0x00720D70)
#include "shared/warhead_type.hpp"

HRESULT __stdcall WarheadTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_WarheadTypeClass;
    return S_OK;
}
