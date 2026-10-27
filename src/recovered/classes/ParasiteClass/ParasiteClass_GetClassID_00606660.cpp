// ?GetClassID@ParasiteClass@@UAGJPAUGUID@@@Z (0x00606660)
// The class identifier.
#include "shared/parasite.hpp"
// @ref _CLSID_ParasiteClass=007a1df0

HRESULT __stdcall ParasiteClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_ParasiteClass;
    return S_OK;
}
