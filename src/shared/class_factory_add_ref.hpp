// TClassFactory<T>::AddRef (one definition; a source includes it and instantiates
// the class, so only this member is emitted).
#ifndef RA2_SHARED_CLASS_FACTORY_ADD_REF_HPP
#define RA2_SHARED_CLASS_FACTORY_ADD_REF_HPP

#include "shared/class_factory.hpp"

template <class T>
unsigned long __stdcall TClassFactory<T>::AddRef()
{
    return InterlockedIncrement(&references);
}

#endif
