// TClassFactory<JumpjetLocomotionClass> COM creation, original 006963b0.
// Light JumpjetLocomotionClass interface: allocation size 144 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0JumpjetLocomotionClass@@QAE@XZ=0052f160

class JumpjetLocomotionClass {
public:
    JumpjetLocomotionClass();
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~JumpjetLocomotionClass();
    unsigned char unknown_04[0x90 - 4];
};

template <>
HRESULT __stdcall TClassFactory<JumpjetLocomotionClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    JumpjetLocomotionClass *instance = new JumpjetLocomotionClass();
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
