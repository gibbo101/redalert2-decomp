// HRESULT __stdcall SmudgeTypeClass::GetClassID(GUID *clsid) (0x00688390)
#include "shared/smudge_type.hpp"
// @ref _CLSID_SmudgeTypeClass=007a1b80

HRESULT __stdcall SmudgeTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_SmudgeTypeClass;
    return S_OK;
}
