// HRESULT __stdcall HouseClass::EnumConnectionPoints(IEnumConnectionPoints **points) (0x004ED340)
// A new enumerator over the house's connection points
// (IConnectionPointContainer).
#include "shared/techno.hpp"

#define E_OUTOFMEMORY ((HRESULT)0x8007000EL)

// The connection point enumerator (0x24 bytes; constructor 0x00492E20).
class UnknownEnumConnectionPoints : public IUnknown {
public:
    UnknownEnumConnectionPoints(DynamicVectorClass<IConnectionPoint *> &points);   // 0x00492E20
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    char unknown_04[0x24 - 4];
};

HRESULT __stdcall HouseClass::EnumConnectionPoints(IEnumConnectionPoints **points)
{
    if (points == 0) {
        return E_POINTER;
    }
    UnknownEnumConnectionPoints *enumerator = new UnknownEnumConnectionPoints(ConnectionPoints);
    if (enumerator == 0) {
        return E_OUTOFMEMORY;
    }
    enumerator->AddRef();
    *points = (IEnumConnectionPoints *)enumerator;
    return S_OK;
}
