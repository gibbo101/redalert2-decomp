// TClassFactory<MechLocomotionClass> COM creation, original 00696fb0.
// Light MechLocomotionClass interface: allocation size 52 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0MechLocomotionClass@@QAE@XZ=005916d0

class MechLocomotionClass {
public:
    MechLocomotionClass();
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~MechLocomotionClass();
    unsigned char unknown_04[0x34 - 4];
};

template <>
HRESULT __stdcall TClassFactory<MechLocomotionClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    MechLocomotionClass *instance = new MechLocomotionClass();
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
