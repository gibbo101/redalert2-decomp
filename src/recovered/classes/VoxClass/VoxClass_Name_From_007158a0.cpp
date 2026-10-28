// char const *VoxClass::Name_From(int index) (0x007158A0): the name of the
// VoxClass at an index, "none" out of range (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_VoxClass_list_00ad0930@@3V?$DynamicVectorClass@PAVVoxClass@@@@A=00ad0930
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec

char const *__fastcall VoxClass::Name_From(int index)
{
    if (index != -1 && index >= 0 && index < unknown_VoxClass_list_00ad0930.Count()) {
        return unknown_VoxClass_list_00ad0930[index]->Name;
    }
    return "none";
}
