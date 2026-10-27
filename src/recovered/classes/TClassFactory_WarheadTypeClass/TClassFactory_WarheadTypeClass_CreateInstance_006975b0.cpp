// HRESULT __stdcall TClassFactory<WarheadTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object) -- 0x006975B0
// Purpose: the COM class factory for WarheadTypeClass: validates the output pointer,
// refuses aggregation, constructs a WarheadTypeClass (0x178 bytes) and queries it
// for iid, destroying it again when the query fails.
// Assumptions: the constructor at 0x00720100 is the recovered WarheadTypeClass constructor. Only the members the factory touches are declared;
// the virtual destructor occupies slot 8 of the primary vtable.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0WarheadTypeClass@@QAE@PBD@Z=00720100
#include "shared/class_factory.hpp"

class WarheadTypeClass {
public:
    WarheadTypeClass(char const *ini_name);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~WarheadTypeClass();

    unsigned char unknown_04[0x178 - 4];
};

template <>
HRESULT __stdcall TClassFactory<WarheadTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) {
        return E_INVALIDARG;
    }
    *object = 0;
    if (outer != 0) {
        return CLASS_E_NOAGGREGATION;
    }
    WarheadTypeClass *instance = new WarheadTypeClass(0);
    if (instance == 0) {
        return E_OUTOFMEMORY;
    }
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) {
        delete instance;
    }
    return result;
}
