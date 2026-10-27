// HRESULT __stdcall ScriptClass::GetClassID(GUID *clsid) (0x00668960)
#include "shared/script.hpp"
// @ref _CLSID_ScriptClass=007a1d10

HRESULT __stdcall ScriptClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_ScriptClass;
    return S_OK;
}
