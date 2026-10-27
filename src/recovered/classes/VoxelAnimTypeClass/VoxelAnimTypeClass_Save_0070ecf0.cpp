// HRESULT __stdcall VoxelAnimTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x0070ECF0)
#include "shared/voxel_anim_type.hpp"
// @ref ?Save@ObjectTypeClass@@UAGJPAUIStream@@H@Z=005d7e60

HRESULT __stdcall VoxelAnimTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = ObjectTypeClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
