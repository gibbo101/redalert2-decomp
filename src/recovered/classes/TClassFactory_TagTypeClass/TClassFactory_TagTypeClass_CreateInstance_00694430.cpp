// TClassFactory<TagTypeClass> COM creation, original 00694430.
// Light TagTypeClass interface: allocation size 164 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0TagTypeClass@@QAE@PBD@Z=006b4570

class TagTypeClass {
public:
    TagTypeClass(char const *name);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~TagTypeClass();
    unsigned char unknown_04[0xA4 - 4];
};

template <>
HRESULT __stdcall TClassFactory<TagTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    TagTypeClass *instance = new TagTypeClass(0);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
