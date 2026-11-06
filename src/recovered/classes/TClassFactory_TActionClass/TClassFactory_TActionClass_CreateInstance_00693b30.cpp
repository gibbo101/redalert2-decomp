// TClassFactory<TActionClass> COM creation, original 00693b30.
// Light TActionClass interface: allocation size 120 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0TActionClass@@QAE@XZ=006ad370

class TActionClass {
public:
    TActionClass();
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~TActionClass();
    unsigned char unknown_04[0x78 - 4];
};

template <>
HRESULT __stdcall TClassFactory<TActionClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    TActionClass *instance = new TActionClass();
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
