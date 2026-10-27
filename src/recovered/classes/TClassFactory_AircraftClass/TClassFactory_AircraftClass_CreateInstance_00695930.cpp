// HRESULT __stdcall TClassFactory<AircraftClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object) -- 0x00695930
// Purpose: the COM class factory for AircraftClass: validates the output pointer,
// refuses aggregation, constructs a AircraftClass (0x5C0 bytes) and queries it
// for iid, destroying it again when the query fails.
// Assumptions: the constructor at 0x00413A40 is the recovered AircraftClass constructor. Only the members the factory touches are declared;
// the virtual destructor occupies slot 8 of the primary vtable.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0AircraftClass@@QAE@PAVAircraftTypeClass@@PAVHouseClass@@@Z=00413a40
#include "shared/class_factory.hpp"

class AircraftTypeClass;
class HouseClass;

class AircraftClass {
public:
    AircraftClass(AircraftTypeClass *type, HouseClass *house);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~AircraftClass();

    unsigned char unknown_04[0x5C0 - 4];
};

template <>
HRESULT __stdcall TClassFactory<AircraftClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) {
        return E_INVALIDARG;
    }
    *object = 0;
    if (outer != 0) {
        return CLASS_E_NOAGGREGATION;
    }
    AircraftClass *instance = new AircraftClass(0, 0);
    if (instance == 0) {
        return E_OUTOFMEMORY;
    }
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) {
        delete instance;
    }
    return result;
}
