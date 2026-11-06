// TClassFactory<DropPodLocomotionClass> COM creation, original 00696b30.
// Light DropPodLocomotionClass interface: allocation size 48 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0DropPodLocomotionClass@@QAE@XZ=004a5a40

class DropPodLocomotionClass {
public:
    DropPodLocomotionClass();
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~DropPodLocomotionClass();
    unsigned char unknown_04[0x30 - 4];
};

template <>
HRESULT __stdcall TClassFactory<DropPodLocomotionClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    DropPodLocomotionClass *instance = new DropPodLocomotionClass();
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
