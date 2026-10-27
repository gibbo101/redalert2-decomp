// The COM class factory template the game instantiates once per creatable
// class (TClassFactory<T>, RTTI names such as TClassFactory<WalkLocomotionClass>).
// Each instantiation has the five IClassFactory methods in one block:
// QueryInterface, AddRef, Release, CreateInstance, LockServer (0x180-byte
// stride from 0x006914F0). Only CreateInstance depends on T.
#ifndef RA2_SHARED_CLASS_FACTORY_HPP
#define RA2_SHARED_CLASS_FACTORY_HPP

#include "shared/com_persist.hpp"

#ifndef E_INVALIDARG
#define E_INVALIDARG ((HRESULT)0x80070057L)
#endif
#ifndef E_OUTOFMEMORY
#define E_OUTOFMEMORY ((HRESULT)0x8007000EL)
#endif
#ifndef CLASS_E_NOAGGREGATION
#define CLASS_E_NOAGGREGATION ((HRESULT)0x80040110L)
#endif

extern "C" GUID const IID_IClassFactory;      // 0x007AFCF0 {00000001-0000-0000-C000-000000000046}

struct __declspec(novtable) IClassFactory : public IUnknown {
    virtual HRESULT __stdcall CreateInstance(IUnknown *outer, GUID const &iid, void **object) = 0;
    virtual HRESULT __stdcall LockServer(int lock) = 0;
};

template <class T>
class TClassFactory : public IClassFactory {
public:
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual HRESULT __stdcall CreateInstance(IUnknown *outer, GUID const &iid, void **object);
    virtual HRESULT __stdcall LockServer(int lock);

private:
    long references;                    // +0x04
};

#endif
