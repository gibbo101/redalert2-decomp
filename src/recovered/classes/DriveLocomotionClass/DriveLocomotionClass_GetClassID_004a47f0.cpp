// HRESULT __stdcall DriveLocomotionClass::GetClassID(GUID *clsid) (0x004A47F0)
#include "shared/drive_locomotion.hpp"
// @ref _CLSID_DriveLocomotionClass=007a1f70

HRESULT __stdcall DriveLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_DriveLocomotionClass;
    return S_OK;
}
