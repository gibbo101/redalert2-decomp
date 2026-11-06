// TClassFactory<AircraftTypeClass> COM creation, original 00694d30.
// Light AircraftTypeClass interface: allocation size 2984 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0AircraftTypeClass@@QAE@PBD@Z=0041bc90

class AircraftTypeClass {
public:
    AircraftTypeClass(char const *name);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~AircraftTypeClass();
    unsigned char unknown_04[0xBA8 - 4];
};

template <>
HRESULT __stdcall TClassFactory<AircraftTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    AircraftTypeClass *instance = new AircraftTypeClass(0);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
