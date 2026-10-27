// static VoxelAnimTypeClass *__fastcall VoxelAnimTypeClass::Find_Or_Make(char const *name) (0x0070ED80)
// The type with this ID, else a new one; null for "<none>" and "none".
#include "shared/voxel_anim_type.hpp"
// @ref ??2@YAPAXI@Z=00782017

VoxelAnimTypeClass *__fastcall VoxelAnimTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < VoxelAnimTypes.Count(); index++) {
        if (_stricmp(VoxelAnimTypes[index]->ID, name) == 0) {
            return VoxelAnimTypes[index];
        }
    }
    return new VoxelAnimTypeClass(name);
}
