// HRESULT __stdcall IsometricTileTypeClass::GetClassID(GUID *clsid) (0x0052E2D0, slot 3)
// Only the list accessors expand here: the colour table constructor stays a call.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"
// @ref _CLSID_IsometricTileTypeClass=007a1b60

HRESULT __stdcall IsometricTileTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_IsometricTileTypeClass;
    return S_OK;
}
