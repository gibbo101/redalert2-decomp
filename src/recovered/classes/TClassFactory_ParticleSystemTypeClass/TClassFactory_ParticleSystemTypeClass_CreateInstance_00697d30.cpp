// TClassFactory<ParticleSystemTypeClass> COM creation, original 00697d30.
// Light ParticleSystemTypeClass interface: allocation size 736 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0ParticleSystemTypeClass@@QAE@PBD@Z=00620600

class ParticleSystemTypeClass {
public:
    ParticleSystemTypeClass(char const *name);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~ParticleSystemTypeClass();
    unsigned char unknown_04[0x2E0 - 4];
};

template <>
HRESULT __stdcall TClassFactory<ParticleSystemTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    ParticleSystemTypeClass *instance = new ParticleSystemTypeClass(0);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
