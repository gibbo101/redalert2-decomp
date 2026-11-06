// TClassFactory<BuildingClass> COM creation, original 006957b0.
// Light BuildingClass interface: allocation size 1504 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0BuildingClass@@QAE@PAVBuildingTypeClass@@PAVHouseClass@@@Z=00438ce0
class BuildingTypeClass;
class HouseClass;

class BuildingClass {
public:
    BuildingClass(BuildingTypeClass *type, HouseClass *house);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~BuildingClass();
    unsigned char unknown_04[0x5E0 - 4];
};

template <>
HRESULT __stdcall TClassFactory<BuildingClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    BuildingClass *instance = new BuildingClass(0, 0);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
