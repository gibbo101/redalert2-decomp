// HRESULT __stdcall WeaponTypeClass::GetClassID(GUID *clsid) (0x00733C50)
#include "shared/weapon_type.hpp"

HRESULT __stdcall WeaponTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_WeaponTypeClass;
    return S_OK;
}
