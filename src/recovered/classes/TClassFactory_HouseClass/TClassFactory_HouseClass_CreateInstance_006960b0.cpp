// TClassFactory<HouseClass> COM creation, original 006960b0.
// Light HouseClass interface: allocation size 90000 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0HouseClass@@QAE@PAVHouseTypeClass@@@Z=004e18c0

class HouseTypeClass;
class HouseClass {
public:
    HouseClass(HouseTypeClass *type);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~HouseClass();
    unsigned char unknown_04[0x15F90 - 4];
};

template <>
HRESULT __stdcall TClassFactory<HouseClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    HouseClass *instance = new HouseClass(0);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
