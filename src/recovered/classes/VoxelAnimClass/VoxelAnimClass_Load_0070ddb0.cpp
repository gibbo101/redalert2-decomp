// HRESULT __stdcall VoxelAnimClass::Load(IStream *stream) (0x0070DDB0)
// Restores the object in place, re-initializes the sound controllers and
// swizzles the pointers; returns ObjectClass::Load's result.
#include "shared/voxel_anim.hpp"
// @ref ?Load@ObjectClass@@UAGJPAUIStream@@@Z=005d4760
// @ref ??0ObjectClass@@QAE@ABVNoInitClass@@@Z=005d2500
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ??_7VoxelAnimClass@@6BIPersistStream@@@=007ae428
// @ref ??_7VoxelAnimClass@@6BIRTTITypeInfo@@@=007ae40c
// @ref ??_7VoxelAnimClass@@6BINoticeSink@@@=007ae404
// @ref ??_7VoxelAnimClass@@6BINoticeSource@@@=007ae3fc

HRESULT __stdcall VoxelAnimClass::Load(IStream *stream)
{
    HRESULT result = ObjectClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) VoxelAnimClass(NoInitClass());
        unknown_fc.Init();
        unknown_110.Init();
        SwizzleManager.Swizzle((void **)&Class);
        SwizzleManager.Swizzle((void **)&unknown_f0);
        SwizzleManager.Swizzle((void **)&unknown_f4);
    }
    return result;
}
