// void Audio_Pause() -- 0x00406DE0
// Purpose: pauses the device's event channels, the events and the
// music hooks' counters (0x007144B0).
#include "shared/audio.hpp"

void unknown_007144b0();    // 0x007144B0

void Audio_Pause()
{
    if (Audio_Main_Device != 0) {
        Audio_Device_Pause_Channels(Audio_Main_Device, 1);
    }
    Audio_Events_Pause();
    unknown_007144b0();
}
