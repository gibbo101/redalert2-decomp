// HRESULT __stdcall HouseClass::QueryInterface(GUID const &iid, void **object) (0x004E29D0)
// IUnknown, IPersist and IPersistStream give the object; IHouse,
// IPublicHouse and IConnectionPointContainer their interfaces.
#include "shared/techno.hpp"

HRESULT __stdcall HouseClass::QueryInterface(GUID const &iid, void **object)
{
    if (object == 0) {
        return E_POINTER;
    }
    *object = 0;
    if (iid == IID_IUnknown_7afce0) {
        *object = static_cast<IPersistStream *>(this);
    }
    if (iid == IID_IHouse) {
        *object = static_cast<IHouse *>(this);
    }
    if (iid == IID_IPublicHouse) {
        *object = static_cast<IPublicHouse *>(this);
    }
    if (iid == IID_IConnectionPointContainer) {
        *object = static_cast<IConnectionPointContainer *>(this);
    }
    if (iid == IID_IPersist) {
        *object = static_cast<IPersistStream *>(this);
    }
    if (iid == IID_IPersistStream) {
        *object = static_cast<IPersistStream *>(this);
    }
    if (*object == 0) {
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}
