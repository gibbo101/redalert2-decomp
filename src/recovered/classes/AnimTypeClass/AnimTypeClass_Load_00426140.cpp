// HRESULT __stdcall AnimTypeClass::Load(IStream *stream) (0x00426140)
// Restores the type in place, reloads its voxel and image, swizzles the
// type pointers and reloads a non-demand-loaded image for the scenario's
// theater.
#include "shared/anim_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?Load@ObjectTypeClass@@UAGJPAUIStream@@@Z=005d7c30
// @ref ?unknown_func_5d6730@ObjectTypeClass@@QAEXXZ=005d6730
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

HRESULT __stdcall AnimTypeClass::Load(IStream *stream)
{
    HRESULT result = ObjectTypeClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) AnimTypeClass(NoInitClass());
    unknown_func_5d6730();
    unknown_func_5d7630();
    SwizzleManager.Swizzle((void **)&Next);
    SwizzleManager.Swizzle((void **)&ExpireAnim);
    SwizzleManager.Swizzle((void **)&TrailerAnim);
    SwizzleManager.Swizzle((void **)&BounceAnim);
    SwizzleManager.Swizzle((void **)&Spawns);
    SwizzleManager.Swizzle((void **)&Warhead);
    SwizzleManager.Swizzle((void **)&TiberiumSpawnType);
    if (!DemandLoad) {
        if (unknown_1fc) {
            char fullname[512];
            _makepath(fullname, 0, 0, ID, Theaters[unknown_id_source_a3d290->Theater].Suffix);
            unknown_a4 = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);
            return S_OK;
        }
        if (unknown_207) {
            unknown_slot40(unknown_id_source_a3d290->Theater);
        }
    }
    return S_OK;
}
