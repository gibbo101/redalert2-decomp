// HRESULT __stdcall ScriptTypeClass::GetClassID(GUID *clsid) (0x006690C0)
#include "shared/script.hpp"
// @ref _CLSID_ScriptTypeClass=007a1d20

HRESULT __stdcall ScriptTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_ScriptTypeClass;
    return S_OK;
}
