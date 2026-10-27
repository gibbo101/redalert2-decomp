// HRESULT __stdcall TClassFactory<BombClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object) -- 0x006933B0
// Purpose: the COM class factory for BombClass: validates the output pointer,
// refuses aggregation, constructs a BombClass (0x5C bytes) and queries it
// for iid, destroying it again when the query fails.
// Assumptions: the constructor at 0x00435BE0 stores the BombClass vtables (RTTI). Only the members the factory touches are declared;
// the virtual destructor occupies slot 8 of the primary vtable.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0BombClass@@QAE@XZ=00435be0
#include "shared/class_factory.hpp"

class BombClass {
public:
    BombClass();
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~BombClass();

    unsigned char unknown_04[0x5C - 4];
};

template <>
HRESULT __stdcall TClassFactory<BombClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) {
        return E_INVALIDARG;
    }
    *object = 0;
    if (outer != 0) {
        return CLASS_E_NOAGGREGATION;
    }
    BombClass *instance = new BombClass();
    if (instance == 0) {
        return E_OUTOFMEMORY;
    }
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) {
        delete instance;
    }
    return result;
}
