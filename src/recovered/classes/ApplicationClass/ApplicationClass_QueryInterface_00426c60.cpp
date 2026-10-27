// HRESULT __stdcall ApplicationClass::QueryInterface(GUID const &iid, void **object) -- 0x00426C60
// IUnknown slot 0: answers IApplication and IUnknown with itself (AddRef),
// and a third interface (0x007A2C28) with the map object at 0x008324E0
// (no AddRef).
#include "shared/application.hpp"
// @ref _IID_IApplication_79c3d0=0079c3d0
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _unknown_iid_7a2c28=007a2c28
// @ref ?unknown_map_object_8324e0@@3DA=008324e0

HRESULT __stdcall ApplicationClass::QueryInterface(GUID const &iid, void **object)
{
    if (object == 0) {
        return E_POINTER;
    }
    if (iid == IID_IApplication_79c3d0 || iid == IID_IUnknown_7afce0) {
        *object = this;
        AddRef();
        return S_OK;
    }
    if (iid == unknown_iid_7a2c28) {
        *object = &unknown_map_object_8324e0;
        return S_OK;
    }
    return E_NOINTERFACE;
}
