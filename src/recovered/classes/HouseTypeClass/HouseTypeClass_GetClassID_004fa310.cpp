// HRESULT __stdcall HouseTypeClass::GetClassID(GUID *classid) (0x004FA310)
// @ref _CLSID_HouseTypeClass=007a1ba0

HRESULT __stdcall HouseTypeClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_HouseTypeClass;
    return S_OK;
}
