// HRESULT __stdcall AbstractClass::QueryInterface(GUID const &iid, void **object) (0x00410000)
// IUnknown: IUnknown, IPersistStream and IPersist give the object, IRTTITypeInfo its +4 interface.
#include "shared/abstract.hpp"
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _IID_IPersistStream=007afcd0
// @ref _IID_IPersist=007afcc0
// @ref _IID_IRTTITypeInfo=007a2020

HRESULT __stdcall AbstractClass::QueryInterface(GUID const &iid, void **object)
{
    if (object == 0) {
        return E_POINTER;
    }
    *object = 0;
    if (iid == IID_IUnknown_7afce0) {
        *object = static_cast<IPersistStream *>(this);
    }
    if (iid == IID_IPersistStream) {
        *object = static_cast<IPersistStream *>(this);
    }
    if (iid == IID_IPersist) {
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
