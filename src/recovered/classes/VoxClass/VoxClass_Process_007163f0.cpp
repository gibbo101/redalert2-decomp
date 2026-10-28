// void VoxClass::Process(CCINIClass &ini) (0x007163F0): makes (or finds) a
// VoxClass for each [DialogList] entry of EVA.ini, which then reads its own
// section (name hypothesis).
#include "shared/vox_speech.hpp"
#include "shared/ccini_class.hpp"
// @ref ??_C@_0L@PLKG@DialogList?$AA@=007f9d74
// @ref ??_C@_00A@?$AA@=0083c55c
void __fastcall VoxClass::Process(CCINIClass &ini)
{
    if (ini.Is_Present("DialogList")) {
        int count = ini.Entry_Count("DialogList");
        for (int index = 0; index < count; index++) {
            char name[200];
            if (ini.Get_String("DialogList", ini.Get_Entry("DialogList", index), "", name, sizeof(name))) {
                VoxClass *vox;
                int vox_index = Find_Index(name);
                if (vox_index == -1) {
                    vox = new VoxClass(name);
                } else {
                    vox = unknown_VoxClass_list_00ad0930[vox_index];
                }
                vox->Read_INI(ini);
            }
        }
    }
}
