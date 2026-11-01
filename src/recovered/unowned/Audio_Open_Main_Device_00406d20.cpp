// int Audio_Open_Main_Device() -- 0x00406D20
// Purpose: creates the default driver and the main device (22050 Hz 16-bit
// stereo PCM) with 16 channels, as Audio_Init does. 1 when it has all 16.
#include "shared/audio.hpp"

int Audio_Open_Main_Device()
{
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
        return 1;
    }
    return 0;
}
