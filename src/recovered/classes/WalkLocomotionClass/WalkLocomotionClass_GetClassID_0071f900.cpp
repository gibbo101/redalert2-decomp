// HRESULT __stdcall WalkLocomotionClass::GetClassID(GUID *clsid) (0x0071F900)
#include "shared/walk_locomotion.hpp"
// @ref _CLSID_WalkLocomotionClass=007a1fa0

HRESULT __stdcall WalkLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_WalkLocomotionClass;
    return S_OK;
}
