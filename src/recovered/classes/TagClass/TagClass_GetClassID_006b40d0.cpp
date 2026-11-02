// HRESULT __stdcall TagClass::GetClassID(GUID *clsid) (0x006B40D0)
#include "shared/tag.hpp"
// @ref _CLSID_TagClass=007a1d30

HRESULT __stdcall TagClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TagClass;
    return S_OK;
}
