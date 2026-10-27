// HRESULT __stdcall TClassFactory<WaveClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object) -- 0x00691730
// Purpose: the COM class factory for WaveClass: validates the output pointer,
// refuses aggregation, constructs a WaveClass (0x208 bytes) and queries it
// for iid, destroying it again when the query fails.
// Assumptions: the constructor at 0x007216D0 builds on ObjectClass and owns a VectorClass<CellClass *>; WaveClass (size 0x208) is inferred, not RTTI-certified for this writer. Only the members the factory touches are declared;
// the virtual destructor occupies slot 8 of the primary vtable.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0WaveClass@@QAE@XZ=007216d0
#include "shared/class_factory.hpp"

class WaveClass {
public:
    WaveClass();
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~WaveClass();

    unsigned char unknown_04[0x208 - 4];
};

template <>
HRESULT __stdcall TClassFactory<WaveClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) {
        return E_INVALIDARG;
    }
    *object = 0;
    if (outer != 0) {
        return CLASS_E_NOAGGREGATION;
    }
    WaveClass *instance = new WaveClass();
    if (instance == 0) {
        return E_OUTOFMEMORY;
    }
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) {
        delete instance;
    }
    return result;
}
