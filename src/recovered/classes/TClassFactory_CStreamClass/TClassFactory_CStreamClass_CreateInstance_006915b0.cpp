// HRESULT __stdcall TClassFactory<CStreamClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object) -- 0x006915B0
// Purpose: the COM class factory for CStreamClass: validates the output pointer,
// refuses aggregation, constructs a CStreamClass (0x2C bytes) and queries it
// for iid, destroying it again when the query fails.
// Assumptions: the constructor at 0x00494800 stores the CStreamClass vtables (RTTI). Only the members the factory touches are declared;
// the virtual destructor follows the eleven IStream methods
// (slot 14 of the primary vtable).
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0CStreamClass@@QAE@XZ=00494800
#include "shared/class_factory.hpp"

class CStreamClass {
public:
    CStreamClass();
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void Read();    // IStream slot 3 (signature not needed here)
    virtual void Write();    // IStream slot 4 (signature not needed here)
    virtual void Seek();    // IStream slot 5 (signature not needed here)
    virtual void SetSize();    // IStream slot 6 (signature not needed here)
    virtual void CopyTo();    // IStream slot 7 (signature not needed here)
    virtual void Commit();    // IStream slot 8 (signature not needed here)
    virtual void Revert();    // IStream slot 9 (signature not needed here)
    virtual void LockRegion();    // IStream slot 10 (signature not needed here)
    virtual void UnlockRegion();    // IStream slot 11 (signature not needed here)
    virtual void Stat();    // IStream slot 12 (signature not needed here)
    virtual void Clone();    // IStream slot 13 (signature not needed here)
    virtual ~CStreamClass();

    unsigned char unknown_04[0x2C - 4];
};

template <>
HRESULT __stdcall TClassFactory<CStreamClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) {
        return E_INVALIDARG;
    }
    *object = 0;
    if (outer != 0) {
        return CLASS_E_NOAGGREGATION;
    }
    CStreamClass *instance = new CStreamClass();
    if (instance == 0) {
        return E_OUTOFMEMORY;
    }
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) {
        delete instance;
    }
    return result;
}
