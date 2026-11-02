// void Audio_Device_Set_Format(AudioDevice *device, AudioFormat const *format) (0x004031B0)
// Copies the format into the device's default format (name hypothesis).
#include "shared/audio.hpp"

void __fastcall Audio_Device_Set_Format(AudioDevice *device, AudioFormat const *format)
{
    device->DefaultFormat = *format;
}
