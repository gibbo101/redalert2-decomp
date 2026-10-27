// HRESULT __stdcall DriveLocomotionClass::QueryInterface(GUID const &iid, void **object) (0x0049F820)
// The base interfaces, then IPiggyback.
#include "shared/drive_locomotion.hpp"
// @ref ?QueryInterface@LocomotionClass@@UAGJABUGUID@@PAPAX@Z=0053d2b0
// @ref _IID_IPiggyback=007a2050

HRESULT __stdcall DriveLocomotionClass::QueryInterface(GUID const &iid, void **object)
{
    HRESULT result = LocomotionClass::QueryInterface(iid, object);
    if (result == E_NOINTERFACE) {
        if (iid == IID_IPiggyback) {
            *object = static_cast<IPiggyback *>(this);
        }
        if (*object == 0) {
            return E_NOINTERFACE;
        }
        AddRef();
        result = S_OK;
    }
    return result;
}
