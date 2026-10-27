// ?GetClassID@FoggedObjectClass@@UAGJPAUGUID@@@Z (0x004C1F40)
// The class identifier.
#include "shared/fogged_object.hpp"
// @ref _CLSID_FoggedObjectClass=007a1ed0

HRESULT __stdcall FoggedObjectClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_FoggedObjectClass;
    return S_OK;
}
