// TClassFactory<TubeClass> COM creation, original 006927b0.
// Light TubeClass interface: allocation size 452 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0TubeClass@@QAE@ABVCell@@H@Z=006ef1d0
class Cell;
extern "C" Cell const data_6927b0_0;
// @ref _data_6927b0_0=00abd408

class TubeClass {
public:
    TubeClass(Cell const &cell, int value);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~TubeClass();
    unsigned char unknown_04[0x1C4 - 4];
};

template <>
HRESULT __stdcall TClassFactory<TubeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    TubeClass *instance = new TubeClass(data_6927b0_0, 0);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
