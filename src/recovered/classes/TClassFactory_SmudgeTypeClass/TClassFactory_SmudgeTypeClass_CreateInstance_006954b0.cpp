// HRESULT __stdcall TClassFactory<SmudgeTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object) -- 0x006954B0
// Purpose: the COM class factory for SmudgeTypeClass: validates the output pointer,
// refuses aggregation, constructs a SmudgeTypeClass (0x274 bytes) and queries it
// for iid, destroying it again when the query fails.
// Assumptions: the constructor at 0x00687DA0 stores the SmudgeTypeClass vtables (RTTI); its parameter type is assumed (INI name, as for the other type classes). Only the members the factory touches are declared;
// the virtual destructor occupies slot 8 of the primary vtable.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0SmudgeTypeClass@@QAE@PBD@Z=00687da0
#include "shared/class_factory.hpp"

class SmudgeTypeClass {
public:
    SmudgeTypeClass(char const *ini_name);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~SmudgeTypeClass();

    unsigned char unknown_04[0x274 - 4];
};

template <>
HRESULT __stdcall TClassFactory<SmudgeTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) {
        return E_INVALIDARG;
    }
    *object = 0;
    if (outer != 0) {
        return CLASS_E_NOAGGREGATION;
    }
    SmudgeTypeClass *instance = new SmudgeTypeClass(0);
    if (instance == 0) {
        return E_OUTOFMEMORY;
    }
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) {
        delete instance;
    }
    return result;
}
