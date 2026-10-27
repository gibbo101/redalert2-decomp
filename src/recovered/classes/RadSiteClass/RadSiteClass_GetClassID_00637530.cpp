// ?GetClassID@RadSiteClass@@UAGJPAUGUID@@@Z (0x00637530)
// The class identifier.
#include "shared/radsite.hpp"
// @ref _CLSID_RadSiteClass=007a1e10

HRESULT __stdcall RadSiteClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_RadSiteClass;
    return S_OK;
}
