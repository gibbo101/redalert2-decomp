// HRESULT __stdcall TeamTypeClass::GetClassID(GUID *clsid) (0x006BFE30)
#include "shared/team_type.hpp"
// @ref _CLSID_TeamTypeClass=007a1cf0

HRESULT __stdcall TeamTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TeamTypeClass;
    return S_OK;
}
