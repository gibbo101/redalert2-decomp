// HRESULT __stdcall TeamClass::GetClassID(GUID *clsid) (0x006BABF0)
#include "shared/team.hpp"
// @ref _CLSID_TeamClass=007a1cd0

HRESULT __stdcall TeamClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TeamClass;
    return S_OK;
}
