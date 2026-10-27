// RulesClass::Voxel_Anims (0x0064C0F0)
// @ref ??_C@_0L@CDKJ@VoxelAnims?$AA@=007f1674
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a VoxelAnimTypeClass for every name listed in [VoxelAnims].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/voxel_anim_type.hpp"

bool RulesClass::Voxel_Anims(CCINIClass &ini)
{
    int count = ini.Entry_Count("VoxelAnims");
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String("VoxelAnims", ini.Get_Entry("VoxelAnims", index), "", buffer, sizeof(buffer))) {
            VoxelAnimTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
