// HRESULT __stdcall OverlayTypeClass::Load(IStream *stream) (0x005DCE10)
// Restores the type in place, reloads its voxel and image, swizzles the
// cell animation and reloads a non-demand-loaded image for the scenario's
// theater.
#include "shared/overlay_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?Load@ObjectTypeClass@@UAGJPAUIStream@@@Z=005d7c30
// @ref ?unknown_func_5d6730@ObjectTypeClass@@QAEXXZ=005d6730
// @ref ?unknown_func_5d7630@ObjectTypeClass@@QAEXXZ=005d7630
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
// @ref ?Theater_Naming_Convention@ObjectTypeClass@@SIXPADH@Z=005d7bd0
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref __makepath=007831f0

HRESULT __stdcall OverlayTypeClass::Load(IStream *stream)
{
    HRESULT result = ObjectTypeClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) OverlayTypeClass(NoInitClass());
        unknown_func_5d6730();
        unknown_func_5d7630();
        SwizzleManager.Swizzle((void **)&CellAnim);
        if (!DemandLoad) {
            char fullname[512];
            if (unknown_1fc) {
                _makepath(fullname, 0, 0, unknown_1c8, Theaters[unknown_id_source_a3d290->Theater].Suffix);
            } else {
                _makepath(fullname, 0, 0, unknown_1c8, ".SHP");
                Theater_Naming_Convention(fullname, unknown_id_source_a3d290->Theater);
            }
            unknown_a4 = (void *)MixFileClass::Retrieve(fullname);
        }
        result = S_OK;
    }
    return result;
}
