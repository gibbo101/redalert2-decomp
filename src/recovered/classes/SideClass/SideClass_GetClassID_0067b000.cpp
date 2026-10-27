// HRESULT __stdcall SideClass::GetClassID(GUID *classid) (0x0067B000)
// @ref _CLSID_SideClass=007a1e50

HRESULT __stdcall SideClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_SideClass;
    return S_OK;
}
