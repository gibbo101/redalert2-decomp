// HRESULT __stdcall TubeClass::GetClassID(GUID *clsid) (0x006EF8D0)
#include "shared/tube.hpp"
// @ref _CLSID_TubeClass=007a1cc0

HRESULT __stdcall TubeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TubeClass;
    return S_OK;
}
