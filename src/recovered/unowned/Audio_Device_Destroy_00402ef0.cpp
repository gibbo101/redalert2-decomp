// void __fastcall Audio_Device_Destroy(AudioDevice *device) -- 0x00402EF0
// Purpose: destroys the device's channels, closes it through its driver,
// frees its slot in the driver (the driver's device count floored at 0)
// and deletes it.
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Device_Destroy(AudioDevice *device)
{
    AudioChannel *node = (AudioChannel *)Audio_List_First(&device->ChannelList);
    AudioChannel *channel = node;
    while (node != 0) {
        node = (AudioChannel *)Audio_List_Next(node);
        Audio_Channel_Destroy(channel);
        channel = node;
    }
    device->Driver->Info->Close(device);
    device->Driver->Devices[device->DriverIndex] = 0;
    if ((device->Driver->DeviceCount -= 1) < 0) {
        device->Driver->DeviceCount = 0;
    }
    operator delete(device);
}
