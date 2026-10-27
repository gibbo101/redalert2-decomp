// TClassFactory<T>::QueryInterface (one definition; a source includes it and
// instantiates the class, so only this member is emitted: VC6 ignores
// explicit instantiation of a single member).
#ifndef RA2_SHARED_CLASS_FACTORY_QUERY_INTERFACE_HPP
#define RA2_SHARED_CLASS_FACTORY_QUERY_INTERFACE_HPP

#include "shared/class_factory.hpp"

// IUnknown and IClassFactory answer with the factory itself.
template <class T>
HRESULT __stdcall TClassFactory<T>::QueryInterface(GUID const &iid, void **object)
{
    if (object == 0) {
        return E_POINTER;
    }
    *object = 0;
    if (iid == IID_IUnknown_7afce0 || iid == IID_IClassFactory) {
        *object = this;
    }
    if (*object == 0) {
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

#endif
