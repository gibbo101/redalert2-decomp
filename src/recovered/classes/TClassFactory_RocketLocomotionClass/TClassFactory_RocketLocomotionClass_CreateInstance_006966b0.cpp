// TClassFactory<RocketLocomotionClass> COM creation, original 006966b0.
// Light RocketLocomotionClass interface: allocation size 88 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0RocketLocomotionClass@@QAE@XZ=0063dac0

class RocketLocomotionClass {
public:
    RocketLocomotionClass();
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~RocketLocomotionClass();
    unsigned char unknown_04[0x58 - 4];
};

template <>
HRESULT __stdcall TClassFactory<RocketLocomotionClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    RocketLocomotionClass *instance = new RocketLocomotionClass();
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
