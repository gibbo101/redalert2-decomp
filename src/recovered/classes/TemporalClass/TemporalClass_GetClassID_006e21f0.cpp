// ?GetClassID@TemporalClass@@UAGJPAUGUID@@@Z (0x006E21F0)
// The class identifier.
#include "shared/temporal.hpp"
// @ref _CLSID_TemporalClass=007a1e20

HRESULT __stdcall TemporalClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_TemporalClass;
    return S_OK;
}
