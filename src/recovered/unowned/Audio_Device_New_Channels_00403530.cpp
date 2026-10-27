// int __fastcall Audio_Device_New_Channels(AudioDevice *device, int count) -- 0x00403530
// Purpose: makes up to count channels (0x004034B0, expanded inline),
// stopping when the device cannot take another. Returns how many were
// made.
#include "shared/audio.hpp"

int __fastcall Audio_Device_New_Channels(AudioDevice *device, int count)
{
    int made = 0;
    do {
        if (Audio_Device_New_Channel(device) == 0) {
            break;
        }
        made++;
    } while (--count != 0);
    return made;
}
