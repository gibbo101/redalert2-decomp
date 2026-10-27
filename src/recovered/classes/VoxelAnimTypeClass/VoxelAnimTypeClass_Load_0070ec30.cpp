// HRESULT __stdcall VoxelAnimTypeClass::Load(IStream *stream) (0x0070EC30)
// Restores the type in place, swizzles its type pointers and reloads its
// voxel.
#include "shared/voxel_anim_type.hpp"
// @ref ?Load@ObjectTypeClass@@UAGJPAUIStream@@@Z=005d7c30
// @ref ??0ObjectTypeClass@@QAE@ABVNoInitClass@@@Z=005d5a80
// @ref ?unknown_func_5d6730@ObjectTypeClass@@QAEXXZ=005d6730
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall VoxelAnimTypeClass::Load(IStream *stream)
{
    HRESULT result = ObjectTypeClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) VoxelAnimTypeClass(NoInitClass());
    SwizzleManager.Swizzle((void **)&Warhead);
    SwizzleManager.Swizzle((void **)&BounceAnim);
    SwizzleManager.Swizzle((void **)&ExpireAnim);
    SwizzleManager.Swizzle((void **)&TrailerAnim);
    SwizzleManager.Swizzle((void **)&Spawns);
    SwizzleManager.Swizzle((void **)&AttachedSystem);
    unknown_func_5d6730();
    return S_OK;
}
