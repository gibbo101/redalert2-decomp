// int Taunt_Init() (0x00715F10): makes the "Taunt Stream" stream (0 without
// one); the global levels 1 and 5 are set on the speech stream (name
// hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_taunt_stream_ad0968@@3PAUAudioStreamPlayer@@A=00ad0968
// @ref ?unknown_vox_stream_ad095c@@3PAUAudioStreamPlayer@@A=00ad095c
// @ref ?unknown_count_ad0910@@3HC=00ad0910
// @ref ?Audio_Global_Levels@@3PAPAUAudioLevelSet@@A=0083144c
// @ref ?Audio_Get_Device@@YAPAUAudioDevice@@XZ=00406f40
// @ref ??_C@_0N@IANH@Taunt?5Stream?$AA@=007f9c48

int Taunt_Init()
{
    if (unknown_taunt_stream_ad0968 == 0) {
        unknown_taunt_stream_ad0968 = Audio_Stream_Create(Audio_Get_Device(), 3000);
        if (unknown_taunt_stream_ad0968 == 0) {
            return 0;
        }
    }
    Audio_Stream_Set_Name(unknown_taunt_stream_ad0968, "Taunt Stream");
    Audio_Stream_Set_Levels_94(unknown_vox_stream_ad095c, Audio_Global_Levels[1]);
    Audio_Stream_Set_Levels_9c(unknown_vox_stream_ad095c, Audio_Global_Levels[5]);
    unknown_count_ad0910 = 0;
    return 1;
}
