// void Audio_Close_Main_Device() -- 0x00406DA0
// Purpose: removes the main device (Audio_Open_Main_Device's) when there is one.
#include "shared/audio.hpp"

void Audio_Close_Main_Device()
{
    if (Audio_Main_Device != 0) {
        Audio_Device_Remove(Audio_Main_Device);
        Audio_Main_Device = 0;
    }
}
