// HRESULT __stdcall TaskForceClass::GetClassID(GUID *clsid) (0x006B70D0)
#include "shared/task_force.hpp"
// @ref _CLSID_TaskForceClass=007a1ce0

HRESULT __stdcall TaskForceClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TaskForceClass;
    return S_OK;
}
