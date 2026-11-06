// TClassFactory<TagClass> COM creation, original 006942b0.
// Light TagClass interface: allocation size 56 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0TagClass@@QAE@PAVTagTypeClass@@@Z=006b3870
class TagTypeClass;

class TagClass {
public:
    TagClass(TagTypeClass *type);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~TagClass();
    unsigned char unknown_04[0x38 - 4];
};

template <>
HRESULT __stdcall TClassFactory<TagClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    TagClass *instance = new TagClass(0);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
