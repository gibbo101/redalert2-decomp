// TClassFactory<HouseTypeClass> COM creation, original 00695f30.
// Light HouseTypeClass interface: allocation size 432 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0HouseTypeClass@@QAE@PBD@Z=004f90f0

class HouseTypeClass {
public:
    HouseTypeClass(char const *name);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~HouseTypeClass();
    unsigned char unknown_04[0x1B0 - 4];
};

template <>
HRESULT __stdcall TClassFactory<HouseTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    HouseTypeClass *instance = new HouseTypeClass(0);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
