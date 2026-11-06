// TClassFactory<IsometricTileTypeClass> COM creation, original 006951b0.
// Light IsometricTileTypeClass interface: allocation size 732 and QI/deleting destructor slots
// are independently present in the accepted original factory body.
#include "shared/class_factory.hpp"
// @ref ??0IsometricTileTypeClass@@QAE@HHEPBD_N@Z=00528ee0

class IsometricTileTypeClass {
public:
    IsometricTileTypeClass(int type, int value, unsigned char mode, char const *name, bool skip);
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~IsometricTileTypeClass();
    unsigned char unknown_04[0x2DC - 4];
};

template <>
HRESULT __stdcall TClassFactory<IsometricTileTypeClass>::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) return E_INVALIDARG;
    *object = 0;
    if (outer != 0) return CLASS_E_NOAGGREGATION;
    IsometricTileTypeClass *instance = new IsometricTileTypeClass(0, 0, 0, 0, false);
    if (instance == 0) return E_OUTOFMEMORY;
    HRESULT result = instance->QueryInterface(iid, object);
    if (FAILED(result)) delete instance;
    return result;
}
