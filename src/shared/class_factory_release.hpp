// TClassFactory<T>::Release (one definition; a source includes it and instantiates
// the class, so only this member is emitted).
#ifndef RA2_SHARED_CLASS_FACTORY_RELEASE_HPP
#define RA2_SHARED_CLASS_FACTORY_RELEASE_HPP

#include "shared/class_factory.hpp"

template <class T>
unsigned long __stdcall TClassFactory<T>::Release()
{
    long remaining = InterlockedDecrement(&references);
    if (remaining == 0) {
        delete this;
    }
    return remaining;
}

#endif
