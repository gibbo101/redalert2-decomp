// int Audio_Shutdown() -- 0x00406C80
// Purpose: shuts the audio library down: the device's channels, the events and streams, the two sound helpers
// (0x00715780, 0x00715F80), the event system and the streamer; then the bag, AUDIO.MIX, THEME.MIX and the device are
// released and the system itself shut down.
#include "shared/mix_file_class.hpp"
#include "shared/cd.hpp"
#include "shared/audio.hpp"
#include "shared/vox_class.hpp"

// @ref ?Speech_Shutdown@@YAXXZ=00715780
// @ref ?unknown_00715f80@@YAXXZ=00715f80
// @ref ?Audio_Events_Shutdown@@YAXXZ=00403f80
// @ref ?Audio_System_Shutdown@@YIHXZ=00402990
void unknown_00715f80();    // 0x00715F80

int Audio_Shutdown()
{
    if (Audio_Main_Device != 0) {
        Audio_Device_Stop_Channels(Audio_Main_Device, 1);
    }
    Audio_Events_Clear();
    Audio_Streams_Stop();
    Speech_Shutdown();
    unknown_00715f80();
    Audio_Events_Shutdown();
    Audio_Streamer_Shutdown();
    if (Audio_Main_Bag != 0) {
        Audio_Bag_Destroy(Audio_Main_Bag);
        Audio_Main_Bag = 0;
    }
    if (AudioMix != 0) {
        delete AudioMix;
        AudioMix = 0;
    }
    if (ThemeMix != 0) {
        delete ThemeMix;
        ThemeMix = 0;
    }
    if (Audio_Main_Device != 0) {
        Audio_Device_Remove(Audio_Main_Device);
        Audio_Main_Device = 0;
    }
    return Audio_System_Shutdown();
}
