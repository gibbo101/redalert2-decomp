// HRESULT __stdcall TClassFactory<SuperWeaponTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object) -- 0x00691BB0
// Purpose: the COM class factory for SuperWeaponTypeClass: validates the output pointer,
// refuses aggregation, constructs a SuperWeaponTypeClass (0xEC bytes) and queries it
// for iid, destroying it again when the query fails.
// Assumptions: the constructor at 0x0069F000 is the recovered SuperWeaponTypeClass constructor. Only the members the factory touches are declared;
// the virtual destructor occupies slot 8 of the primary vtable.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0SuperWeaponTypeClass@@QAE@PBD@Z=0069f000
#include "shared/class_factory.hpp"

class SuperWeaponTypeClass {
public:
    SuperWeaponTypeClass(char const *ini_name);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~SuperWeaponTypeClass();

    unsigned char unknown_04[0xEC - 4];
};

template <>
HRESULT __stdcall TClassFactory<SuperWeaponTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) {
        return E_INVALIDARG;
    }
    *object = 0;
    if (outer != 0) {
        return CLASS_E_NOAGGREGATION;
    }
    SuperWeaponTypeClass *instance = new SuperWeaponTypeClass(0);
    if (instance == 0) {
        return E_OUTOFMEMORY;
    }
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) {
        delete instance;
    }
    return result;
}
