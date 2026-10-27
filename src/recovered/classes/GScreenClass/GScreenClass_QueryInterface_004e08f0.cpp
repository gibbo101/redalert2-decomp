// HRESULT __stdcall GScreenClass::QueryInterface(GUID const &iid, void **object) (0x004E08F0, slot 0)
// IUnknown and IGameMap give the screen itself.
#include "shared/gscreen.hpp"
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _IID_IGameMap=007a2c28

HRESULT __stdcall GScreenClass::QueryInterface(GUID const &iid, void **object)
{
    if (object == 0) {
        return E_POINTER;
    }
    if (!(iid == IID_IUnknown_7afce0) && !(iid == IID_IGameMap)) {
        return E_NOINTERFACE;
    }
    *object = this;
    AddRef();
    return S_OK;
}
