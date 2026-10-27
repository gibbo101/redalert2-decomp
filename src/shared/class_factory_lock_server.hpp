// TClassFactory<T>::LockServer (one definition; a source includes it and instantiates
// the class, so only this member is emitted).
#ifndef RA2_SHARED_CLASS_FACTORY_LOCK_SERVER_HPP
#define RA2_SHARED_CLASS_FACTORY_LOCK_SERVER_HPP

#include "shared/class_factory.hpp"

template <class T>
HRESULT __stdcall TClassFactory<T>::LockServer(int lock)
{
    if (lock) {
        references++;
    } else {
        references--;
    }
    return S_OK;
}

#endif
