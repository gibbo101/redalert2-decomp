// HRESULT __stdcall HouseClass::GetClassID(GUID *clsid) (0x004EE850)
#include "shared/techno.hpp"

HRESULT __stdcall HouseClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_HouseClass;
    return S_OK;
}
