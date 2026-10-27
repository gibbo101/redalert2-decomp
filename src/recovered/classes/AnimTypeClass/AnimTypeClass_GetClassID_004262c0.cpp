// HRESULT __stdcall AnimTypeClass::GetClassID(GUID *clsid) (0x004262C0)
#include "shared/anim_type.hpp"
// @ref _CLSID_AnimTypeClass=007a1b90

HRESULT __stdcall AnimTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_AnimTypeClass;
    return S_OK;
}
