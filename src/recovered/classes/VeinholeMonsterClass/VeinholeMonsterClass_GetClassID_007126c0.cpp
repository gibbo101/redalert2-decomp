// HRESULT __stdcall VeinholeMonsterClass::GetClassID(GUID *clsid) (0x007126C0)
#include "shared/veinhole.hpp"
// @ref _CLSID_VeinholeMonsterClass=007a1ef0

HRESULT __stdcall VeinholeMonsterClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_VeinholeMonsterClass;
    return S_OK;
}
