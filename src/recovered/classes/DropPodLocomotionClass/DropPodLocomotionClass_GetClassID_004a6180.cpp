// HRESULT __stdcall DropPodLocomotionClass::GetClassID(GUID *clsid) (0x004A6180)
#include "shared/droppod_locomotion.hpp"
// @ref _CLSID_DropPodLocomotionClass=007a1fb0

HRESULT __stdcall DropPodLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_DropPodLocomotionClass;
    return S_OK;
}
