// void __fastcall Audio_Stop() -- 0x00406DC0
// Purpose: stops the device's event channels and clears the events.
#include "shared/audio.hpp"

void __fastcall Audio_Stop()
{
    if (Audio_Main_Device != 0) {
        Audio_Device_Stop_Channels(Audio_Main_Device, 1);
    }
    Audio_Events_Clear();
}
