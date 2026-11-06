// TClassFactory<FoggedObjectClass> COM creation, original 006981b0.
// Light FoggedObjectClass interface: allocation size 120 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0FoggedObjectClass@@QAE@XZ=004c0020

class FoggedObjectClass {
public:
    FoggedObjectClass();
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~FoggedObjectClass();
    unsigned char unknown_04[0x78 - 4];
};

template <>
HRESULT __stdcall TClassFactory<FoggedObjectClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    FoggedObjectClass *instance = new FoggedObjectClass();
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
