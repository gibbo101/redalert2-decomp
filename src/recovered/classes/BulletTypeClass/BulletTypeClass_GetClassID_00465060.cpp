// HRESULT __stdcall BulletTypeClass::GetClassID(GUID *clsid) (0x00465060)
#include "shared/bullet_type.hpp"

HRESULT __stdcall BulletTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_BulletTypeClass;
    return S_OK;
}
