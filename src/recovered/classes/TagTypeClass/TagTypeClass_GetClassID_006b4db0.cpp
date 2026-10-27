// HRESULT __stdcall TagTypeClass::GetClassID(GUID *clsid) (0x006B4DB0)
#include "shared/object.hpp"

HRESULT __stdcall TagTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TagTypeClass;
    return S_OK;
}
