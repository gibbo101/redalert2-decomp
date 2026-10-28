// int VoxClass::Index_Of(VoxClass *vox) (0x00716740): the index of a VoxClass
// in the unit's list, -1 for none.
#include "shared/vox_speech.hpp"

int __fastcall VoxClass::Index_Of(VoxClass *vox)
{
    for (int index = 0; index < unknown_VoxClass_list_00ad0930.Count(); index++) {
        if (unknown_VoxClass_list_00ad0930[index] == vox) {
            return index;
        }
    }
    return -1;
}
