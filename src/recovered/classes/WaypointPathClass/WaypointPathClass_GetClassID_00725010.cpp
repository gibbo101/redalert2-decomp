// WaypointPathClass GetClassID (0x725010)
#include "shared/waypoint_path.hpp"
// @ref _CLSID_WaypointPathClass=007a1dc0

HRESULT __stdcall WaypointPathClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_WaypointPathClass;
    return S_OK;
}

