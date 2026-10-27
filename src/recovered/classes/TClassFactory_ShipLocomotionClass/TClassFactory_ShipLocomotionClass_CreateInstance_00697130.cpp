// HRESULT __stdcall TClassFactory<ShipLocomotionClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object) -- 0x00697130
// Purpose: the COM class factory for ShipLocomotionClass: validates the output pointer,
// refuses aggregation, constructs a ShipLocomotionClass (0x70 bytes) and queries it
// for iid, destroying it again when the query fails.
// Assumptions: the constructor at 0x00675600 stores the ShipLocomotionClass vtables (RTTI). Only the members the factory touches are declared;
// the virtual destructor occupies slot 8 of the primary vtable.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0ShipLocomotionClass@@QAE@XZ=00675600
#include "shared/class_factory.hpp"

class ShipLocomotionClass {
public:
    ShipLocomotionClass();
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~ShipLocomotionClass();

    unsigned char unknown_04[0x70 - 4];
};

template <>
HRESULT __stdcall TClassFactory<ShipLocomotionClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) {
        return E_INVALIDARG;
    }
    *object = 0;
    if (outer != 0) {
        return CLASS_E_NOAGGREGATION;
    }
    ShipLocomotionClass *instance = new ShipLocomotionClass();
    if (instance == 0) {
        return E_OUTOFMEMORY;
    }
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) {
        delete instance;
    }
    return result;
}
