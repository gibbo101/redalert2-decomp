// HRESULT SwizzleManagerClass::QueryInterface(GUID const &, void **) (0x0069FD10, slot 0)
// ISwizzle and IUnknown.
#include "shared/swizzle.hpp"

// @ref _IID_ISwizzle=007a2060
// @ref _IID_IUnknown_7afce0=007afce0

HRESULT __stdcall SwizzleManagerClass::QueryInterface(GUID const &iid, void **object)
{
    if (object == 0) {
        return E_POINTER;
    }
    if (iid == IID_ISwizzle || iid == IID_IUnknown_7afce0) {
        *object = this;
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}
