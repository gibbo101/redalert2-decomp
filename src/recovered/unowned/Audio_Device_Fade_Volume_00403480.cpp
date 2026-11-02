// void Audio_Device_Fade_Volume(AudioDevice *device, int volume) (0x00403480)
// Ramps the device's master volume to the value (name hypothesis).
#include "shared/audio.hpp"
// @ref ?Set_Target@AudioLevel@@QAIXH@Z=004070a0

void __fastcall Audio_Device_Fade_Volume(AudioDevice *device, int volume)
{
    device->Levels.Volume.Set_Target(volume);
}
