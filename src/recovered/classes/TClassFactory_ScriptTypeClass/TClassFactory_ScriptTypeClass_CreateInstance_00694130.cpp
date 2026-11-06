// TClassFactory<ScriptTypeClass> COM creation, original 00694130.
// Light ScriptTypeClass interface: allocation size 564 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0ScriptTypeClass@@QAE@PBD@Z=00668a20

class ScriptTypeClass {
public:
    ScriptTypeClass(char const *name);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~ScriptTypeClass();
    unsigned char unknown_04[0x234 - 4];
};

template <>
HRESULT __stdcall TClassFactory<ScriptTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    ScriptTypeClass *instance = new ScriptTypeClass(0);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
