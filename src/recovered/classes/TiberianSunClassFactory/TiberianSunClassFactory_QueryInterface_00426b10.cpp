// HRESULT __stdcall TiberianSunClassFactory::QueryInterface(GUID const &iid, void **object) -- 0x00426B10
// IUnknown slot 0: answers IClassFactory and IUnknown with the factory itself (AddRef).
#include "shared/tiberian_sun_class_factory.hpp"
// @ref _IID_IClassFactory=007afcf0
// @ref _IID_IUnknown_7afce0=007afce0

HRESULT __stdcall TiberianSunClassFactory::QueryInterface(GUID const &iid, void **object)
{
    if (object == 0) {
        return E_POINTER;
    }
    if (iid == IID_IClassFactory || iid == IID_IUnknown_7afce0) {
        *object = this;
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}
