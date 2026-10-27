// HRESULT __stdcall HouseTypeClass::QueryInterface(GUID const &iid, void **object) (0x004FA270)
// Same answers as AbstractClass::QueryInterface (its own copy).

HRESULT __stdcall HouseTypeClass::QueryInterface(GUID const &iid, void **object)
{
    if (object == 0) {
        return E_POINTER;
    }
    *object = 0;
    if (iid == IID_IUnknown_7afce0) {
        *object = static_cast<IPersistStream *>(this);
    }
    if (iid == IID_IPersist) {
        *object = static_cast<IPersistStream *>(this);
    }
    if (iid == IID_IPersistStream) {
        *object = static_cast<IPersistStream *>(this);
    }
    if (iid == IID_IRTTITypeInfo) {
        *object = static_cast<IRTTITypeInfo *>(this);
    }
    if (*object == 0) {
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}
