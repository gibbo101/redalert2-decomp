// HRESULT __stdcall AircraftTypeClass::GetClassID(GUID *clsid) (0x0041C210)
#include "shared/aircraft_type.hpp"
// @ref _unknown_clsid_aircraft_type_7a1b20=007a1b20

HRESULT __stdcall AircraftTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = unknown_clsid_aircraft_type_7a1b20;
    return S_OK;
}
