// void Audio_Resume_All() -- 0x00406E70
// Purpose: undoes Audio_Pause_All.
#include "shared/audio.hpp"

void unknown_007144f0();    // 0x007144F0
void unknown_007168e0();    // 0x007168E0
void unknown_007169f0();    // 0x007169F0

void Audio_Resume_All()
{
    unknown_007168e0();
    unknown_007169f0();
    unknown_007144f0();
    Audio_Events_Resume();
    if (Audio_Main_Device != 0) {
        Audio_Device_Resume_Channels(Audio_Main_Device, 1);
    }
}
