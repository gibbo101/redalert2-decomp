// HRESULT __stdcall SuperClass::GetClassID(GUID *classid) (0x0069E9B0)
// @ref _CLSID_SuperClass=007a1af0

HRESULT __stdcall SuperClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_SuperClass;
    return S_OK;
}
