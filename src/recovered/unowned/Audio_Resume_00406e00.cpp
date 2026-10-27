// void Audio_Resume() -- 0x00406E00
// Purpose: undoes Audio_Pause.
#include "shared/audio.hpp"

void unknown_007144f0();    // 0x007144F0

void Audio_Resume()
{
    unknown_007144f0();
    Audio_Events_Resume();
    if (Audio_Main_Device != 0) {
        Audio_Device_Resume_Channels(Audio_Main_Device, 1);
    }
}
