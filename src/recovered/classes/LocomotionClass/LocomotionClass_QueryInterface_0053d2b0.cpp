// HRESULT __stdcall LocomotionClass::QueryInterface(GUID const &iid, void **object) (0x0053D2B0)
// IUnknown and ILocomotion give the +4 interface, IPersistStream and
// IPersist the object.
#include "shared/locomotion.hpp"
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _IID_IPersistStream=007afcd0
// @ref _IID_ILocomotion=007a5890
// @ref _IID_IPersist=007afcc0

HRESULT __stdcall LocomotionClass::QueryInterface(GUID const &iid, void **object)
{
    if (object == 0) {
        return E_POINTER;
    }
    *object = 0;
    if (iid == IID_IUnknown_7afce0) {
        *object = static_cast<ILocomotion *>(this);
    }
    if (iid == IID_IPersistStream) {
        *object = static_cast<IPersistStream *>(this);
    }
    if (iid == IID_ILocomotion) {
        *object = static_cast<ILocomotion *>(this);
    }
    if (iid == IID_IPersist) {
        *object = static_cast<IPersistStream *>(this);
    }
    if (*object == 0) {
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}
