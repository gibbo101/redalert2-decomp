// void Audio_Pause_All() -- 0x00406E40
// Purpose: Audio_Pause plus the two 0x007169xx layers.
#include "shared/audio.hpp"

void unknown_007144b0();    // 0x007144B0
void unknown_00716980();    // 0x00716980
void unknown_007168d0();    // 0x007168D0

void Audio_Pause_All()
{
    if (Audio_Main_Device != 0) {
        Audio_Device_Pause_Channels(Audio_Main_Device, 1);
    }
    Audio_Events_Pause();
    unknown_007144b0();
    unknown_00716980();
    unknown_007168d0();
}
