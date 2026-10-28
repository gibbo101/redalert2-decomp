// void Speech_Cancel(int index) (0x00715E80): drops every waiting speech of
// the VoxClass at an index, marking it idle (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_VoxClass_list_00ad0930@@3V?$DynamicVectorClass@PAVVoxClass@@@@A=00ad0930
// @ref ?unknown_vox_pending_ad0948@@3PAUVoxSpeech@@A=00ad0948
// @ref ?Speech_Find@@YIPAUVoxSpeech@@PAVVoxClass@@@Z=00715ac0

void __fastcall Speech_Cancel(int index)
{
    if (index >= 0 && index < unknown_VoxClass_list_00ad0930.Count()) {
        VoxSpeech *speech;
        while ((speech = Speech_Find(unknown_VoxClass_list_00ad0930[index])) != 0) {
            if (speech->Prev != speech) {
                Audio_List_Remove(speech);
            }
            if (speech == unknown_vox_pending_ad0948) {
                unknown_vox_pending_ad0948 = 0;
            }
            speech->Vox->State = 2;
            delete speech;
        }
    }
}
