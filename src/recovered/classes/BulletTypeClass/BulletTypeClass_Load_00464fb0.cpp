// HRESULT __stdcall BulletTypeClass::Load(IStream *stream) (0x00464FB0)
// Restores the type in place, reloads its voxel and image and swizzles its
// trailer and weapon pointers.
#include "shared/bullet_type.hpp"
// @ref ?Load@ObjectTypeClass@@UAGJPAUIStream@@@Z=005d7c30
// @ref ??0ObjectTypeClass@@QAE@ABVNoInitClass@@@Z=005d5a80
// @ref ?unknown_func_5d6730@ObjectTypeClass@@QAEXXZ=005d6730
// @ref ?unknown_func_5d7630@ObjectTypeClass@@QAEXXZ=005d7630
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall BulletTypeClass::Load(IStream *stream)
{
    HRESULT result = ObjectTypeClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) BulletTypeClass(NoInitClass());
    unknown_func_5d6730();
    unknown_func_5d7630();
    SwizzleManager.Swizzle((void **)&Trailer);
    SwizzleManager.Swizzle((void **)&AirburstWeapon);
    SwizzleManager.Swizzle((void **)&ShrapnelWeapon);
    return S_OK;
}
