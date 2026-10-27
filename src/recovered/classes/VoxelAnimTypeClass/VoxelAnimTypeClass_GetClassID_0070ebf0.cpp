// HRESULT __stdcall VoxelAnimTypeClass::GetClassID(GUID *clsid) (0x0070EBF0)
#include "shared/voxel_anim_type.hpp"
// @ref _CLSID_VoxelAnimTypeClass=007a1d00

HRESULT __stdcall VoxelAnimTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_VoxelAnimTypeClass;
    return S_OK;
}
