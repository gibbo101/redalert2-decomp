// HRESULT __stdcall TerrainTypeClass::Load(IStream *stream) (0x006E5950)
// Restores the type in place, reloads its voxel and image and points the
// occupation list at the foundation's list again.
#include "shared/terrain_type.hpp"
// @ref ?Load@ObjectTypeClass@@UAGJPAUIStream@@@Z=005d7c30
// @ref ?unknown_func_5d6730@ObjectTypeClass@@QAEXXZ=005d6730
// @ref ?unknown_func_5d7630@ObjectTypeClass@@QAEXXZ=005d7630
// @ref ?unknown_foundation_lists_ac0430@@3PAY09VCell@@A=00ac0430

HRESULT __stdcall TerrainTypeClass::Load(IStream *stream)
{
    HRESULT result = ObjectTypeClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) TerrainTypeClass(NoInitClass());
        unknown_func_5d6730();
        unknown_func_5d7630();
        OccupyList = unknown_foundation_lists_ac0430[Foundation];
        result = S_OK;
    }
    return result;
}
