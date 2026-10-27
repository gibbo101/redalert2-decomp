// static int __fastcall VoxelAnimTypeClass::From_Name(char const *name) (0x0070EA60)
// Index of the type with this ID (case-insensitive), or -1.
#include "shared/voxel_anim_type.hpp"
// @ref __stricmp=00781f20

int __fastcall VoxelAnimTypeClass::From_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < VoxelAnimTypes.Count(); index++) {
            if (_stricmp(VoxelAnimTypes[index]->ID, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}
