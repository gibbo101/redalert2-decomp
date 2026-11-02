// int __fastcall Audio_Init(int enable) -- 0x00406AD0
// Purpose: starts the audio library: resets the global level sets, and when
// enabled opens the driver and a 22 kHz 16-bit stereo device with 16 channels,
// AUDIO.MIX and the "audio" bag. Starts the streamer and the event system.
// Anything that fails turns the audio off (Audio_Is_On = 0). Always returns 1.
#include "shared/mix_file_class.hpp"
#include "shared/cd.hpp"
#include "shared/audio.hpp"

void unknown_007156d0();    // 0x007156D0
void unknown_00715f10();    // 0x00715F10

int __fastcall Audio_Init(int enable)
{
    Audio_Timer_Init();
    Audio_Level_Set_830fd8.Init();
    Audio_Global_Levels[0] = &Audio_Level_Set_830fd8;
    Audio_Level_Set_8311f8.Init();
    Audio_Global_Levels[2] = &Audio_Level_Set_8311f8;
    Audio_Level_Set_831290.Init();
    Audio_Global_Levels[1] = &Audio_Level_Set_831290;
    Audio_Level_Set_831168.Init();
    Audio_Global_Levels[3] = &Audio_Level_Set_831168;
    Audio_Level_Set_831058.Init();
    Audio_Global_Levels[4] = &Audio_Level_Set_831058;
    Audio_Level_Set_8313b0.Init();
    Audio_Global_Levels[6] = &Audio_Level_Set_8313b0;
    Audio_Level_Set_831310.Init();
    Audio_Global_Levels[5] = &Audio_Level_Set_831310;
    Audio_Level_Set_8310d8.Init();
    Audio_Global_Levels[7] = &Audio_Level_Set_8310d8;
    if (enable != 0) {
        Audio_System_Init();
        Audio_Create_Driver(Audio_Default_Driver);
        AudioFormat format;
        Audio_Format_Init(&format);
        format.Rate = 22050;
        format.Type = AUDIO_FORMAT_PCM;
        format.Channels = 2;
        format.BytesPerSample = 2;
        format.unknown_00 = 4;
        format.Update_Rate();
        Audio_Main_Device = Audio_Create_Device(-1, &format);
        if (Audio_Main_Device != 0 && Audio_Device_New_Channels(Audio_Main_Device, 16) == 16) {
            Audio_Global_Levels[0] = &Audio_Main_Device->Levels;
            AudioMix = new MixFileClass("AUDIO.MIX", &FastKey);
            Audio_Main_Bag = Audio_Bag_Create("audio", 0);
            if (Audio_Main_Bag == 0) {
                enable = 0;
            }
        } else {
            enable = 0;
        }
    }
    Audio_Streamer_Init();
    if (Audio_Events_Init(Audio_Main_Device, Audio_Main_Bag) == 0) {
        enable = 0;
    }
    unknown_007156d0();
    unknown_00715f10();
    Audio_Is_On = enable;
    return 1;
}
