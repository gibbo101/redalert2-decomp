// int Speech_Init() (0x007156D0): empties the speech lists, enables speech and
// makes the "EVA Stream" stream with the global levels 1 and 5 (0 without a
// stream; name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_vox_list_ad0868@@3UAudioListNode@@A=00ad0868
// @ref ?unknown_vox_ad0878@@3HC=00ad0878
// @ref ?unknown_vox_list_ad0890@@3UAudioListNode@@A=00ad0890
// @ref ?unknown_countdown_ad08c8@@3HC=00ad08c8
// @ref ?unknown_vox_lists_ad08e0@@3PAUAudioListNode@@A=00ad08e0
// @ref ?unknown_vox_pending_ad0948@@3PAUVoxSpeech@@A=00ad0948
// @ref ?unknown_vox_enabled_ad094c@@3HA=00ad094c
// @ref ?unknown_vox_stream_ad095c@@3PAUAudioStreamPlayer@@A=00ad095c
// @ref ?Audio_Global_Levels@@3PAPAUAudioLevelSet@@A=0083144c
// @ref ??_C@_0L@BPPF@EVA?5Stream?$AA@=007f9c3c
// @ref ?Audio_Get_Device@@YAPAUAudioDevice@@XZ=00406f40

int Speech_Init()
{
    unknown_vox_ad0878 = 0;
    unknown_countdown_ad08c8 = 0;
    for (int i = 0; i < 4; i++) {
        Audio_List_Init(&unknown_vox_lists_ad08e0[i]);
    }
    Audio_List_Init(&unknown_vox_list_ad0890);
    Audio_List_Init(&unknown_vox_list_ad0868);
    unknown_vox_pending_ad0948 = 0;
    unknown_vox_enabled_ad094c = 1;
    if (unknown_vox_stream_ad095c == 0) {
        unknown_vox_stream_ad095c = Audio_Stream_Create(Audio_Get_Device(), 3000);
        if (unknown_vox_stream_ad095c == 0) {
            return 0;
        }
    }
    Audio_Stream_Set_Name(unknown_vox_stream_ad095c, "EVA Stream");
    Audio_Stream_Set_Levels_94(unknown_vox_stream_ad095c, Audio_Global_Levels[1]);
    Audio_Stream_Set_Levels_9c(unknown_vox_stream_ad095c, Audio_Global_Levels[5]);
    return 1;
}
