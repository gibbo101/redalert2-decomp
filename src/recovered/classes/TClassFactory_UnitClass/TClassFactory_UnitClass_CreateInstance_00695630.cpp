// TClassFactory<UnitClass> COM creation, original 00695630.
// Light UnitClass interface: allocation size 2000 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0UnitClass@@QAE@PAVUnitTypeClass@@PAVHouseClass@@@Z=006fa400
class UnitTypeClass;
class HouseClass;

class UnitClass {
public:
    UnitClass(UnitTypeClass *type, HouseClass *house);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~UnitClass();
    unsigned char unknown_04[0x7D0 - 4];
};

template <>
HRESULT __stdcall TClassFactory<UnitClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    UnitClass *instance = new UnitClass(0, 0);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
