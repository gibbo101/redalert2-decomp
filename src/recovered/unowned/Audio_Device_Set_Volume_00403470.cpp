// void Audio_Device_Set_Volume(AudioDevice *device, int volume) (0x00403470)
// Sets the device's master volume at once (name hypothesis).
#include "shared/audio.hpp"
// @ref ?Set@AudioLevel@@QAIXH@Z=00407080

void __fastcall Audio_Device_Set_Volume(AudioDevice *device, int volume)
{
    device->Levels.Volume.Set(volume);
}
