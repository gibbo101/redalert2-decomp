// HRESULT __stdcall AircraftClass::QueryInterface(GUID const &iid, void **object) (0x00413FA0, slot 0)
// AbstractClass's interfaces, then IFlyControl (the +0x5A8 part).
#include "shared/aircraft.hpp"
// @ref ?QueryInterface@AbstractClass@@UAGJABU_GUID@@PAPAX@Z=00410000
// @ref _IID_IFlyControl=007a2080

HRESULT __stdcall AircraftClass::QueryInterface(GUID const &iid, void **object)
{
    HRESULT result = FootClass::QueryInterface(iid, object);
    if (FAILED(result)) {
        if (iid == IID_IFlyControl) {
            *object = static_cast<IFlyControl *>(this);
        }
        result = S_OK;
        AddRef();
    }
    return result;
}
