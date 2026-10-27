// HRESULT __stdcall SuperWeaponTypeClass::GetClassID(GUID *classid) (0x0069F1F0)
// @ref _CLSID_SuperWeaponTypeClass=007a1ae0

HRESULT __stdcall SuperWeaponTypeClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_SuperWeaponTypeClass;
    return S_OK;
}
