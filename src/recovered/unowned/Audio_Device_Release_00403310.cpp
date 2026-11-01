// void Audio_Device_Release(AudioDevice *device) (0x00403310)
// Drops one user of the device (the count never goes below 0); the last
// user removes the device from the system's list and destroys it.
#include "shared/audio.hpp"

void __fastcall Audio_Device_Release(AudioDevice *device)
{
    if (--device->RefCount < 0) {
        device->RefCount = 0;
    }
    if (device->RefCount == 0) {
        Audio_Device_Remove(device);
    }
}
