// ?GetClassID@SpawnManagerClass@@UAGJPAUGUID@@@Z (0x0068A790)
// The class identifier.
#include "shared/spawn_manager.hpp"
// @ref _CLSID_SpawnManagerClass=007a1dd0

HRESULT __stdcall SpawnManagerClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_SpawnManagerClass;
    return S_OK;
}
