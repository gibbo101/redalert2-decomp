// VoxelAnimTypeClass *__fastcall Find_Or_Make_Type(char const *name, DynamicVectorClass<VoxelAnimTypeClass *> &list) (0x0070EF40)
// The type with this ID in a list, else a new one; null for "<none>" and
// "none". Read_INI calls it for Spawns. Name hypothesis.
#include "shared/voxel_anim_type.hpp"

#pragma auto_inline(off)
VoxelAnimTypeClass *__fastcall Find_Or_Make_Type(char const *name, DynamicVectorClass<VoxelAnimTypeClass *> &list)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < list.Count(); index++) {
        if (_stricmp(list[index]->ID, name) == 0) {
            return list[index];
        }
    }
    return new VoxelAnimTypeClass(name);
}
#pragma auto_inline(on)
