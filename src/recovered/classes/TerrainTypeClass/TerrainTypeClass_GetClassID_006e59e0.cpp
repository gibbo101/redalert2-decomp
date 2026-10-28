// HRESULT __stdcall TerrainTypeClass::GetClassID(GUID *clsid) (0x006E59E0)
#include "shared/terrain_type.hpp"
// @ref _CLSID_TerrainTypeClass=007a1b50

HRESULT __stdcall TerrainTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TerrainTypeClass;
    return S_OK;
}
