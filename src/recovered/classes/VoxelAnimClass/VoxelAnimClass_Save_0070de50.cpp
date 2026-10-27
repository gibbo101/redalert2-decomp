// HRESULT __stdcall VoxelAnimClass::Save(IStream *stream, BOOL clear_dirty) (0x0070DE50)
#include "shared/voxel_anim.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall VoxelAnimClass::Save(IStream *stream, BOOL clear_dirty)
{
    return AbstractClass::Save(stream, clear_dirty);
}
