// void Speech_Play(int index, int type, int priority) (0x007158C0): plays the
// VoxClass at an index unless it is playing already; type 2 drops the type 3
// speeches and stops the speech playing first (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_VoxClass_list_00ad0930@@3V?$DynamicVectorClass@PAVVoxClass@@@@A=00ad0930
// @ref ?unknown_vox_list_ad0868@@3UAudioListNode@@A=00ad0868
// @ref ?unknown_vox_ad0878@@3HC=00ad0878
// @ref ?unknown_vox_playing_ad0954@@3PAVVoxClass@@A=00ad0954
// @ref ?unknown_vox_stream_ad095c@@3PAUAudioStreamPlayer@@A=00ad095c
// @ref ?unknown_vox_delay_ad0960@@3_KA=00ad0960
// @ref ?Speech_Find@@YIPAUVoxSpeech@@PAVVoxClass@@@Z=00715ac0
// @ref ?Speech_Queue@@YIXPAVVoxClass@@HH@Z=007159d0
// @ref ?Speech_Update@@YAXXZ=00715ba0

void __fastcall Speech_Play(int index, int type, int priority)
{
    if (unknown_vox_stream_ad095c != 0 && index >= 0 && index < unknown_VoxClass_list_00ad0930.Count()
            && unknown_vox_ad0878 == 0) {
        VoxClass *vox = unknown_VoxClass_list_00ad0930[index];
        if (vox != unknown_vox_playing_ad0954) {
            if (type == -1) {
                type = vox->Type;
            }
            if (priority == -1) {
                priority = vox->Priority;
            }
            if (unknown_vox_playing_ad0954 != 0 && type == 2) {
                VoxSpeech *speech;
                while ((speech = (VoxSpeech *)Audio_List_First(&unknown_vox_list_ad0868)) != 0) {
                    Audio_List_Remove(speech);
                    speech->Vox->State = 2;
                    delete speech;
                }
                Speech_Stop(true);
                unknown_vox_delay_ad0960 = 0;
            }
            VoxSpeech *speech = Speech_Find(vox);
            if (speech == 0 || speech->Type != type) {
                Speech_Queue(vox, type, priority);
            }
            Speech_Update();
        }
    }
}
